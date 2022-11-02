package game.positions;

import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.actors.ActorLocationsIterator;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.positions.Ground;
import edu.monash.fit2099.engine.positions.Location;
import game.Resettable;
import game.Status;
import game.actions.Jump;
import game.actions.Teleport;
import game.actors.PiranhaPlant;


public class WarpPipe extends Ground implements Resettable {

    Location oldLocation;
    GameMap gameMap;
    int counter = 0;



    ActorLocationsIterator actorLocations = new ActorLocationsIterator();
    //WorldTracker mapTracker = new WorldTracker(new ArrayList<GameMap>());

    public WarpPipe() {
        super('C');
    }

    public WarpPipe(GameMap gamemap){
        super('C');
        this.gameMap = gamemap;
        this.registerInstance();
    }

    /**
     *
     * @param oldLocation This parameter represents the Location the Player was when the Player decided to Teleport
     * @param gamemap This parameter represents the GameMap the Player has decided to travel to
     *
     * This Class extended from the Ground provides Players an entry to and out of Lava Zone. This specifically works
     * as whenever Warp Pipes are generated, their parameter "gamemap" is the opposite of the GameMap they spawned in.
     * Example: Generating a Warp Pipe in the Original World will have the param "gamemap" set to Lava Zone, and vice versa.
     * This allows the Player to switch between Maps, and in the case they do return back to where they once were. The
     * parameter "oldLocation" is called and the Player is moved to that "oldLocation".
     */

    public WarpPipe(Location oldLocation, GameMap gamemap){
        super('C');
        this.oldLocation = oldLocation;
        this.gameMap = gamemap;
    }

    @Override
    public void tick(Location location) {
        counter++;

        if (this.hasCapability(Status.RESETTING) && !location.containsAnActor()){
            counter = 1;
            this.removeCapability(Status.RESETTING);
        }

        if (counter == 1 && gameMap.isAnActorAt(gameMap.at(5,0))){ //Only spawns Piranha Plants in original world
            location.addActor(new PiranhaPlant());
        }
    }

    @Override
    public ActionList allowableActions(Actor actor, Location location, String direction) {
        ActionList actions = new ActionList();
        if(location.containsAnActor()) {
            actions.add(new Teleport(this, location, direction, gameMap, oldLocation));
        }
        if(!location.containsAnActor()) {
            actions.add(new Jump(this, location, direction));
        }
        return actions;
    }

    @Override
    public boolean canActorEnter(Actor actor) {
        return false;
    }

    public GameMap targetLocation(){
        return gameMap;
    }


    @Override
    public void resetInstance() {
        this.addCapability(Status.RESETTING);
    }


}
