import './style.css';
import { fromEvent, interval, merge} from 'rxjs'; 
import { map, filter, scan, flatMap, tap} from 'rxjs/operators';

/*
The following code has implemented the minimum requirement with some features from the full game 
requirement such as : 
- Multiple distinct target areas that must be "filled" 
- At least 3 distinct objects with different behaviours (cars, crocodile, magicalTurtle)
- At least one of the "ground" and "water" sections, including including at least one row in the
  middle where there are no objects (safe zone)
- Smooth and usable game play.

Author : Tin Nguyen 
Student ID: 32480768
*/

type Key = 'ArrowLeft' | 'ArrowRight' | 'ArrowUp' | 'ArrowDown' | 'Space' 
type Event = 'keydown' | 'keyup'


function frogs(){

  const svg = document.querySelector("#svgCanvas") as SVGElement & HTMLElement;
  
  ///////////////THE CREATION OF THE MAP///////////////
 
  const safeZones = document.createElementNS(svg.namespaceURI, "rect"); 
    safeZones.setAttribute("width", svg.getAttribute("width"));
    safeZones.setAttribute("height", "80"); 
    safeZones.setAttribute("x", "0"); 
    safeZones.setAttribute("y", "0");
    safeZones.setAttribute("fill", "#800080");
    svg.appendChild(safeZones);
  
  const safeZonesMiddle = document.createElementNS(svg.namespaceURI, "rect"); 
    safeZonesMiddle.setAttribute("width", svg.getAttribute("width"));
    safeZonesMiddle.setAttribute("height", "40"); 
    safeZonesMiddle.setAttribute("x", "0"); 
    safeZonesMiddle.setAttribute("y", "240");
    safeZonesMiddle.setAttribute("fill", "#800080");
    svg.appendChild(safeZonesMiddle);

  const safeZonesEnd = document.createElementNS(svg.namespaceURI, "rect"); 
    safeZonesEnd.setAttribute("width", svg.getAttribute("width"));
    safeZonesEnd.setAttribute("height", "80"); 
    safeZonesEnd.setAttribute("x", "0"); 
    safeZonesEnd.setAttribute("y", "380");
    safeZonesEnd.setAttribute("fill", "#800080");
    svg.appendChild(safeZonesEnd);

  const river = document.createElementNS(svg.namespaceURI, "rect"); 
    river.setAttribute("width", svg.getAttribute("width"));
    river.setAttribute("x", "0"); 
    river.setAttribute("y", "280");
    river.setAttribute("height", "100"); 
    river.setAttribute("fill", "#05B3D7");
    svg.appendChild(river)

  const score = document.createElementNS(svg.namespaceURI, "text")!;
    score.setAttribute("id", "score")
    score.setAttribute("x", "10")
    score.setAttribute("y", "600")
    score.setAttribute("style", "font-size: 25px; fill: white");
    score.textContent = "Score: 0"; 
    svg.appendChild(score)

  const instructions = document.createElementNS(svg.namespaceURI, "text")!;
    instructions.setAttribute("id", "instructions")
    instructions.setAttribute("x", "300")
    instructions.setAttribute("y", "500")
    instructions.setAttribute("style", "font-size: 25px; fill: white");
    instructions.textContent = "Move Left: ←"; 
    svg.appendChild(instructions)
  
  const instructions2 = document.createElementNS(svg.namespaceURI, "text")!;
    instructions2.setAttribute("id", "instructions")
    instructions2.setAttribute("x", "300")
    instructions2.setAttribute("y", "530")
    instructions2.setAttribute("style", "font-size: 25px; fill: white");
    instructions2.textContent = "Move Right: →"; 
    svg.appendChild(instructions2)

  const instructions3 = document.createElementNS(svg.namespaceURI, "text")!;
    instructions3.setAttribute("id", "instructions")
    instructions3.setAttribute("x", "300")
    instructions3.setAttribute("y", "560")
    instructions3.setAttribute("style", "font-size: 25px; fill: white");
    instructions3.textContent = "Move Down: ↓"; 
    svg.appendChild(instructions3)

  const instructions4 = document.createElementNS(svg.namespaceURI, "text")!;
    instructions4.setAttribute("id", "instructions")
    instructions4.setAttribute("x", "300")
    instructions4.setAttribute("y", "590")
    instructions4.setAttribute("style", "font-size: 25px; fill: white");
    instructions4.textContent = "Move Up: ↑"; 
    svg.appendChild(instructions4)
  
  const frog = document.createElementNS(svg.namespaceURI, "circle");
    frog.setAttribute("r", "10");
    frog.setAttribute("cx", "40");
    frog.setAttribute("cy", "40");
    frog.setAttribute("fill", "green");
    svg.appendChild(frog);
  
  const Constants = {
    startCarCount: 7, 
    startLogCount: 5,
    startTime: 0
  }

  type ViewType = 'frog' | 'car' | 'log' | 'finalPlatform' | 'endCircle' | 'crocodile' | 'turtle'

  class Tick {constructor(public readonly elapsed:number) {}}
  class horizontalMove {constructor(public readonly distance:number){}}
  class verticalMove {constructor(public readonly travel:number){}}

  /////// THE CONTROLS FOR THE GAME  ///////
  const gameClock = interval(10).pipe(map(elapsed => new Tick(elapsed))),
  keyObservable = <T>(e: Event, k:Key, result: () => T) => 
    fromEvent<KeyboardEvent>(document, e).
      pipe(
        filter(({code, key}) => key === k || code === k), 
        filter(({repeat}) => !repeat), 
        map(result)),

    startLeftMove = keyObservable('keydown', 'ArrowLeft', () => new horizontalMove(-20)),
    startRightMove = keyObservable('keydown', 'ArrowRight', () => new horizontalMove(20)),

    stopLeftMove = keyObservable('keyup', 'ArrowLeft', () => new horizontalMove(0)),
    stopRightMove = keyObservable('keyup', 'ArrowRight', () => new horizontalMove(0)),

    startUpMove = keyObservable('keydown', 'ArrowUp', () => new verticalMove(-20)),
    startDownMove = keyObservable('keydown', 'ArrowDown', () => new verticalMove(20)),

    stopUpMove = keyObservable('keyup', 'ArrowUp', () => new verticalMove(0)),
    stopDownMove = keyObservable('keyup', 'ArrowDown', () => new verticalMove(0))

    
    
  type Circle = Readonly<{posx: number, posy: number, radius: number}>
  type ObjectId = Readonly<{id: string, createTime: number, speed: number,}>

  interface IBody extends Circle, ObjectId {
    speed: number 
    width: number, 
    height: number,
    viewType: ViewType
    dangerous: boolean //This is specifically indicated for our enemy "Crocodile"
  }
  
  type Body = Readonly<IBody>

  type State =  {
    time: number, 
    frog: Body, 
    logs: ReadonlyArray<Body>, //This is the array of the logs inside the river 
    collidedWithLogs: ReadonlyArray<Body>, //This is the array of logs that has collided with the frog 
    cars: ReadonlyArray<Body>, //This is the array of cars inside the road 
    crocodiles: ReadonlyArray<Body>, //This is the array of crocodiles in the middle of the river
    magicalTurtle: ReadonlyArray<Body>, //This is the array of the magical turtle inside the first safe zone 
    exit: ReadonlyArray<Body>, // Array of objects that has been sent out of bounds 
    endCircles: ReadonlyArray<Body>, // This is an array of distinct areas that must be filled
    collidedEndCircles: ReadonlyArray<Body>, // Array of distinct areas that has been filled
    stick: boolean // Boolean to indicate whether the frog has stuck itself to a log 
    score: number 
    gameOver: boolean
  }

  const createRect = (viewType: ViewType) => (width: number) => (dangerous:boolean) => (oid: ObjectId) => (circ: Circle) => 
    <Body> {
      ...oid, 
      ...circ, 
      width: width,
      height: 20, 
      id: viewType + oid.id, 
      viewType: viewType,
      dangerous: dangerous
    },
    ///// RECTANGLE OBJECTS /////
    createCar = createRect('car')(50)(true),
    createLog = createRect('log')(80)(false),
    createCrocodile = createRect('crocodile')(60)(false),
    createFinalPlatform = createRect('finalPlatform')(120)(false)
  
  const createCircle = (viewType: ViewType) => (oid: ObjectId) => (circ: Circle) => 
  <Body> {
    ...oid, 
    ...circ, 
    width: 0,
    height: 0, 
    id: viewType + oid.id, 
    viewType: viewType
  }, 
  ///// CIRCLE OBJECTS /////
  createEndCircle = createCircle('endCircle'),
  createMagicalTurtle = createCircle('turtle')

  function createFrog(): Body{
    return {
      id: 'circle',
      viewType: 'frog',
      posx: 50,
      posy: 50, 
      speed: 0,
      width: 0,
      height: 0,
      radius: 10,
      createTime: 0,
      dangerous: false
    }  
  }

  ///// SPAWNING THE CARS  /////
  const carDirectionForward = [...Array(Constants.startCarCount)].map((_,i)=> 600 - 100*i)

  const startCarForward = [...Array(Constants.startCarCount)].map((_,i) => 
  createCar({id: String(i), createTime: 0, speed: 1})
  ({posx: carDirectionForward[i], posy: 100, radius: 10}))

  const startCarBackward = [...Array(Constants.startCarCount)].map((_,i) => 
  createCar({id: String(startCarForward.length + i), createTime: 0, speed: -1})
  ({posx: carDirectionForward[i], posy: 160, radius: 10}))

  const fastStartCarBackward = [...Array(Constants.startCarCount - 3)].map((_,i) => 
  createCar({id: String(startCarForward.length*2 + i), createTime: 0, speed: -5})
  ({posx: 150*i, posy: 200, radius: 10}))

  const startCar = startCarForward.concat(startCarBackward).concat(fastStartCarBackward) 
  
  ///// SPAWNING THE LOGS /////

  const logDirectionForward = [...Array(Constants.startLogCount)].map((_,i) => 600 - (600/Constants.startLogCount)*i)
  
  const startLogForward = [...Array(Constants.startLogCount)].map((_,i) => 
  createLog({id: String(i), createTime: 0, speed: -1.5})
  ({posx: logDirectionForward[i], posy: 280, radius: 10}))
  
  
  const startLogForward2 = [...Array(Constants.startLogCount)].map((_,i) => 
  createLog({id: String(Constants.startLogCount + i), createTime: 0, speed: -2.5})
  ({posx: logDirectionForward[i], posy: 300, radius: 10}))

  const startCrocodiles = [...Array(6)].map((_,i) => 
  createCrocodile({id: String("croc"+i), createTime: 0, speed: 0})
  ({posx: logDirectionForward[i], posy: 320, radius: 10}))

  const startLogForward4 = [...Array(Constants.startLogCount)].map((_,i) => 
  createLog({id: String(Constants.startLogCount*3 + 4 + i), createTime: 0, speed: -1.5})
  ({posx: logDirectionForward[i], posy: 340, radius: 10}))

  const startFinalPlatform = [...Array(3)].map((_,i) => 
  createFinalPlatform({id: "platform" + String(i), createTime: 0, speed: 1.5})
  ({posx: Number(svg.getAttribute("width")) - 250*i , posy: 360, radius: 10}))
  
  const startLog = startLogForward.concat(startLogForward2).concat(startLogForward4).concat(startFinalPlatform)

  //SPAWNING END CIRCLES 

  const startEndCircle = [...Array(5)].
  map((_,i) => createEndCircle( {id: String(i), createTime: 0, speed: 0})({posx: 540 - 120*i , posy: 400, radius: 20}))
  
  //SPAWNING MAGICAL TURTLE 

  const arrayOfMagicalTurtles = [...Array(1)]
  .map((_,i) => createMagicalTurtle( {id: "oogway", createTime: 0, speed: 0})({posx: 550 , posy: 30, radius: 15}))

  const initialState: State = {
      time: 0, 
      frog: createFrog(), 
      logs: startLog,
      cars: startCar,
      collidedWithLogs: [],
      crocodiles: startCrocodiles,
      exit: [],
      endCircles: startEndCircle,
      collidedEndCircles: [],
      magicalTurtle: arrayOfMagicalTurtles,
      stick: false,
      score: 0,
      gameOver: false
    }

  const moveObj = (o: Body) => <Body>{ //Provides an object the ability to move based on their speed
    ...o, 
    posx: o.posx - o.speed 
  }

  const dangerous = (o: Body) => (dangerous: boolean) => <Body>{ // Changes whether an object is dangerous or not 
    ...o, 
    dangerous: dangerous
  }
  

 ///// HANDLES COLLISIONS BETWEEN THE FROG AND OBJECTS /////
  const handleCollisions = (s:State) => {
    const 
    
      carCollided = (a:Body) => a.posx <= s.frog.posx && a.posx + a.width >= s.frog.posx 
                                    && a.posy <= s.frog.posy && a.posy + a.height >= s.frog.posy && a.viewType === 'car',

      logCollided = (a:Body) => a.posx <= s.frog.posx && a.posx + a.width >= s.frog.posx 
                                    && a.posy <= s.frog.posy && a.posy + a.height >= s.frog.posy && 
                                    (a.viewType === 'log' || a.viewType === 'finalPlatform' || a.viewType === 'crocodile'),

      endCircleCollided = (a:Body) => a.posx + (a.radius/2) >= s.frog.posx 
                                      && a.posx - (a.radius/2) <= s.frog.posx && 
                                      a.posy + (a.radius/2) >= s.frog.posy && 
                                      a.posy - (a.radius/2) <= s.frog.posy && 
                                      (a.viewType == 'endCircle' ||  a.viewType == 'turtle'),

      riverCollided = 0 <= s.frog.posx 
                && 600 >= s.frog.posx 
                && 280 <= s.frog.posy 
                && 280 + Number(river.getAttribute("height")) >= s.frog.posy,

      carKilledFrog = s.cars.filter(r => carCollided(r)).length > 0,
      
      frogTouchedEnd = s.endCircles.filter(r => endCircleCollided(r)),

      frogTouchedRiverRect = s.logs.filter(r => logCollided(r))
      .concat(s.crocodiles.filter(croc => logCollided(croc))
      .filter(croc => croc.dangerous === false)),
      
      stickCollided = frogTouchedRiverRect.length > 0,

      magicalTurtleCollided = s.magicalTurtle.filter(s => endCircleCollided(s)).length > 0,

      eatenAlive = s.crocodiles.filter(croc => logCollided(croc)).filter(croc => croc.dangerous === true).length > 0

      
      return({
        ...s, 
        //If the frog has touched the magicalCircle, free teleport to the end !
        frog: magicalTurtleCollided ? {...s.frog, posx: 100, posy: 400} : s.frog,

        //True if the collided end circle is not the ones you have already touched 
        collidedEndCircles: s.collidedEndCircles[0] != frogTouchedEnd[0] ? 
        frogTouchedEnd.concat(s.collidedEndCircles) : s.collidedEndCircles,
        
        //collidedWithLogs will take the array of either the log touched or end circle
        collidedWithLogs: frogTouchedRiverRect.length > 0 ? 
        frogTouchedRiverRect : frogTouchedEnd.length > 0 ? 
        frogTouchedEnd : frogTouchedRiverRect,
        

        score: frogTouchedEnd.length > 0 ? s.score + 1 : s.score,

        //True if a log or end circle is being touched 
        stick: stickCollided,

        gameOver: (riverCollided && !stickCollided) || eatenAlive || carKilledFrog  ? true : carKilledFrog 
          
      })
  }

  
   ///// HANDLES THE OBJECTS EXITING OUTSIDE OF THE GAME /////
  const tick = (s: State, elapse: number) => {
    const not = <T>(f:(x:T) => boolean) => (x:T) => !f(x), 
      
      // Function for objects that move backwards to be resetted
      expiredBackward = (b:Body) => (b.posx < -2*b.width - 30),
      
      //Array of cars that move backwards placed back inside the game
      expiredCarsBackward:Body[] = s.cars.filter(expiredBackward).
          map(mia => 
            createCar({id: String(mia.id), createTime: mia.createTime, speed: mia.speed})
                     ({posx: 600, posy: mia.posy, radius: 10})),
      
      //Function for objects that move forward to be resetted
      expiredForward = (b:Body) => (b.posx > 600 + b.width), 
      
      //Array of cars that move forward placed back inside the game
      expiredCarsForward: Body[] = s.cars.filter(expiredForward).
          map(mia => 
            createCar({id: String(mia.id), createTime: mia.createTime, speed: mia.speed})
                    ({posx: -mia.width, posy: mia.posy, radius: 10})),

      //Array of cars that is still within boundary 
      activeCars = s.cars.filter(not(expiredBackward))
      .filter(not(expiredForward))
      .concat(expiredCarsBackward).concat(expiredCarsForward),
      
      //Array of logs that move forwards outside of boundary 
      expiredLogsForward = s.logs.filter(expiredForward)
      .map(mia => 
        createLog({id: String(mia.id), createTime: mia.createTime, speed: mia.speed})
        ({posx: mia.width*-1, posy: mia.posy, radius: 10})),
      
      //Array of platforms that's outside the boundary 
      expiredFinalPlatforms = s.logs.filter(expiredBackward)
      .map(mia => 
        createFinalPlatform({id: String(mia.id), createTime: mia.createTime, speed: mia.speed})
        ({posx: 600, posy: mia.posy, radius: 10})),
      
      //Array of objects inside the river that is still within boundary 
      activeLogs = s.logs.filter(not(expiredForward))
      .filter(not(expiredBackward))
      .concat(expiredLogsForward).concat(expiredFinalPlatforms),
      
      //Array of cars that has left the boundary 
      expiredCars = s.cars.filter(expiredBackward)
      .concat(s.cars.filter(expiredForward))
      .concat(expiredFinalPlatforms).concat(expiredLogsForward)
    
    
    return handleCollisions({...s, 
      //If the frog has colided with either an end circle or a log inside the river, 
      //the frog is immediately stuck onto that object right in the center, otherwise 
      // it moves nomrally 
      frog : s.collidedWithLogs.length > 0 ? 
      s.collidedWithLogs[0].viewType === 'endCircle' ? 
      {...s.frog, posx: 50, posy: 50} : {...s.frog, posx: s.stick ? 
      (s.collidedWithLogs[0].posx*2 + s.collidedWithLogs[0].width) / 2 : s.frog.posx} : //
      {...s.frog, posx: s.stick ? (s.collidedWithLogs[0].posx*2 + s.collidedWithLogs[0].width) / 2 : s.frog.posx},

      //The pattern for the crocodile when to bite or not 
      crocodiles: s.logs[0].posx > 500 ? s.crocodiles.map(croc => dangerous(croc)(true)) : s.crocodiles.map(croc => dangerous(croc)(false)),
      cars: activeCars.map(moveObj),
      logs: activeLogs.map(moveObj),
      exit: expiredCars, 
      time: elapse,
      stick: s.stick
    })
  }

  // Handles the key inputs
  const reduceState = (s:State, e:horizontalMove|verticalMove|Tick) => 
    e instanceof horizontalMove ? {...s, frog: {...s.frog, posx: s.frog.posx + e.distance}}:
    e instanceof verticalMove   ? {...s, frog: {...s.frog, posx: s.frog.posx, posy: s.frog.posy + e.travel}} : 
    tick(s, e.elapsed); 
  

  const subscription = 
  merge(gameClock,
    startLeftMove,startRightMove,
    stopLeftMove,stopRightMove,
    startDownMove, stopDownMove, 
    startUpMove, stopUpMove,
    )
  .pipe(
    scan(reduceState, initialState))
  .subscribe(updateView)
  
  // Updates the state of the game and how it appears 
  function updateView(s : State): void {
    const svg = document.querySelector("#svgCanvas") as SVGElement & HTMLElement;
    frog.setAttribute("cx", String(s.frog.posx));
    frog.setAttribute("cy", String(s.frog.posy));
    
    //Set their attributes onto the canvas 
    const updateBodyView = (b:Body) => {
      function createBodyView(){
        const v = b.viewType === 'endCircle' || b.viewType === 'turtle'  ?  
        document.createElementNS(svg.namespaceURI, "circle") : 
        document.createElementNS(svg.namespaceURI, "rect")!;
        v.setAttribute("id", b.id);
        b.viewType === 'endCircle' ||b.viewType === 'turtle' ? 
        v.setAttribute("r", String(b.radius)) : false; 
        b.viewType === 'endCircle' || b.viewType === 'turtle' ?  
        v.setAttribute("cy", String(b.posy)) : false;
        b.viewType === 'finalPlatform' ? v.setAttribute("width", "120") : v.setAttribute("width", String(b.width))
        v.setAttribute("height", String(b.height));

        b.viewType === 'car' ? v.setAttribute("fill", "#05B3D7") : 
        b.viewType === 'endCircle' || b.viewType === 'crocodile' ? v.setAttribute("fill", "green") : v.setAttribute("fill", "#964B00")

        v.classList.add(b.viewType)
        svg.appendChild(v)
        svg.append(frog)
        return v;
      }

      const v = document.getElementById(b.id) || createBodyView(); 
      b.viewType === 'endCircle' || b.viewType === 'turtle' ? 
      v.setAttribute("cx", String(b.posx)) : v.setAttribute("x", String(b.posx)); 

      b.viewType === 'endCircle' ||b.viewType === 'turtle' ? 
      v.setAttribute("cy", String(b.posy)) : v.setAttribute("y", String(b.posy));
  
  };

    s.cars.forEach(updateBodyView);
    s.logs.forEach(updateBodyView);
    s.crocodiles.forEach(updateBodyView);
    s.endCircles.forEach(updateBodyView);
    s.magicalTurtle.forEach(updateBodyView);

    //Removes the element outside the boundary 
    s.exit.forEach(o => {
      const v = document.getElementById(o.id); 
      if(v) svg.removeChild(v);
    })
    
    //Upon the collision with either logs or end circles
    if(s.collidedWithLogs.length > 0){
      frog.setAttribute("cx", String((s.collidedWithLogs[0].posx*2 + s.collidedWithLogs[0].width)/2))

      //If it's an end circle, mark the indicated collided circle red 
      s.collidedWithLogs[0].viewType === 'endCircle' ? document.getElementById("score").textContent = "Score:" + String(s.score) : null
      s.collidedWithLogs[0].viewType === 'endCircle' ? document.getElementById(s.collidedEndCircles[0].id).setAttribute("cy", "450") : null
      s.collidedWithLogs[0].viewType === 'endCircle' ? document.getElementById(s.collidedEndCircles[0].id).setAttribute("style", "fill: red;") : null

      //If all end-circles have been collided, show the victory screen !
      if(s.collidedEndCircles.length === 5){
        const victory = document.createElementNS(svg.namespaceURI, "text")!;
          victory.setAttribute("id", "victory")
          victory.setAttribute("x", "0")
          victory.setAttribute("y", "60")
          victory.setAttribute("style", "font-size: 64px; fill: green");
          victory.textContent = "YOU WON"
          svg.appendChild(victory)
        subscription.unsubscribe();
      }
    }
    
    // Red = dangerous, Green = not dangerous - simple.
    if(s.crocodiles[0].dangerous){
      s.crocodiles.forEach(croc => document.getElementById(croc.id).setAttribute("fill", "red"))
    } else {
      s.crocodiles.forEach(croc => document.getElementById(croc.id).setAttribute("fill", "green"))
    }
  
    // If the frog were to go outside of boundary, then it'll be obliterated.
    if(s.frog.posx < 0 || s.frog.posx > 600 || s.frog.posy > 460){
      const v = document.createElementNS(svg.namespaceURI, "text")!;
      v.setAttribute("id", "text")
      v.setAttribute("x", "0")
      v.setAttribute("y", "60")
      v.setAttribute("style", "font-size: 64px; fill: red");
      v.textContent = "OUT OF BOUNDS"
      svg.appendChild(v)
      
      subscription.unsubscribe();
    }

    //If the frog gets killed by any other reasons, it'll show the game over sign
    if(s.gameOver){
      const v = document.createElementNS(svg.namespaceURI, "text")!;
      v.setAttribute("id", "text")
      v.setAttribute("x", "0")
      v.setAttribute("y", "60")
      v.setAttribute("style", "font-size: 64px; fill: red");
      v.textContent = "YOU DIED"
      svg.appendChild(v)
      subscription.unsubscribe();
      frog.setAttribute("style",
      "fill: red; stroke: red; stroke-width: 1px;"
      );
    }
  
  
  }
}

setTimeout(frogs, 0);

