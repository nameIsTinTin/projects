package game;

import java.util.Arrays;
import java.util.List;
import java.util.Random;

import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.actors.ActorLocationsIterator;
import edu.monash.fit2099.engine.displays.Display;
import edu.monash.fit2099.engine.positions.*;
import game.actors.*;
import game.items.Coin;
import game.items.Essence;
import game.items.PowerStar;
import game.items.SuperMushroom;
import game.magicalfountain.HealthFountain;
import game.magicalfountain.PowerFountain;
import game.positions.*;

/**
 * The main class for the Mario World game.
 *
 */
public class Application {

    public static void main(String[] args) {

        World world = new World(new Display());

        FancyGroundFactory groundFactory = new FancyGroundFactory(new Dirt(), new Wall(), new Floor(), new Tree());
        ActorLocationsIterator LocationTester = new ActorLocationsIterator();
        List<String> map = Arrays.asList(
                "..........................................##..........+.........................",
                "............+............+..................#...................................",
                "............................................#...................................",
                ".............................................##......................+..........",
                "...............................................#................................",
                "................................................#...............................",
                ".................+................................#.............................",
                ".................................................##.............................",
                "................................................##..............................",
                ".........+..............................+#____####.................+............",
                ".......................................+#_____###++.............................",
                ".......................................+#______###..............................",
                "........................................+#_____###..............................",
                "........................+........................##.............+...............",
                "...................................................#............................",
                "....................................................#...........................",
                "...................+.................................#..........................",
                "......................................................#.........................",
                ".......................................................##.......................");

        GameMap gameMap = new GameMap(groundFactory, map);
        world.addGameMap(gameMap);

        Actor mario = new Player("Player", 'm', 100);
        world.addPlayer(mario, gameMap.at(42, 10));

        Coin coin = new Coin(200);
        gameMap.at(42,10).addItem(coin);

        // FIXME: the Goomba should be generated from the Tree
//			gameMap.at(43, 10).addActor(new Koopa());

        gameMap.at(44, 11).addActor(new Toad());

        //Put some sprouts randomly on map (REQ1)

        int maxXMap = gameMap.getXRange().max();
        int maxYMap = gameMap.getYRange().max();
        for (int i = 0; i < 10; i++) {
            Random rand = new Random();
            int randomX = rand.nextInt(maxXMap);
            int randomY = rand.nextInt(maxYMap);
            Sprout sprout = new Sprout();
            if (gameMap.at(randomX, randomY).getDisplayChar() == '.')
                gameMap.at(randomX, randomY).setGround(sprout);

        }


        //Place Super Mushroom on the same ground when you instantiate the Player

        //SuperMushroom superMushroom = new SuperMushroom();
        //gameMap.at(42, 10).addItem(superMushroom);


//        Place Power Star
//        PowerStar powerStar = new PowerStar();
//        gameMap.at(42, 10).addItem(powerStar);


        gameMap.at(44, 10).setGround(new PowerFountain());
//        gameMap.at(45,10).setGround(new HealthFountain());





        //Creation of Lava Zone
        FancyGroundFactory lava_groundFactory = new FancyGroundFactory(new Dirt(), new Fence(), new Lava());

        List<String> lava_map = Arrays.asList(
                "..............................................................",
                "..............................................................",
                "..............................................................",
                "....................%L...............L%.......................",
                "....................%LLLL%.......%LLLL%.......................",
                "..............................................................",
                "..............................................................",
                "...................%%%%%...%%.%%...%%%%%......................",
                "....................%...%%%.....%%%...%.......................",
                ".....................%...%.......%...%........................",
                "......................%.............%.........................",
                ".......................%..%.....%..%..........................",
                "........................%%%%%%%%%%%...........................",
                "..............................................................",
                "..............................................................");

        GameMap LavaMap = new GameMap(lava_groundFactory, lava_map);
        world.addGameMap(LavaMap);



        LavaMap.at(29, 10).addActor(new Bowser());

        LavaMap.at(29, 11).addActor(new PrincessPeach());

        //Placing random lavas
        int maxXLavaMap = LavaMap.getXRange().max();
        int maxYLavaMap = LavaMap.getYRange().max();
        for (int i = 0; i < 20; i++) {
            Random rand = new Random();
            int randomX = rand.nextInt(maxXLavaMap);
            int randomY = rand.nextInt(maxYLavaMap);
            Lava hot_floor = new Lava();
            if (LavaMap.at(randomX, randomY).getDisplayChar() == '.') {
                LavaMap.at(randomX, randomY).setGround(hot_floor);
            }
        }

        //WarpPipe warpPipe = new WarpPipe(LavaMap);

        int maxXWarpMap = gameMap.getXRange().max();
        int maxYWarpMap = gameMap.getYRange().max();
        for (int i = 0; i < 10; i++) {
            Random rando = new Random();
            int randomWarpX = rando.nextInt(maxXWarpMap);
            int randomWarpY = rando.nextInt(maxYWarpMap);

            if (gameMap.at(randomWarpX, randomWarpY).getDisplayChar() == '.') {
                gameMap.at(randomWarpX, randomWarpY).setGround(new WarpPipe(LavaMap));
            }
        }


            gameMap.at(42, 8).setGround(new WarpPipe(LavaMap));

        FancyGroundFactory end_groundFactory = new FancyGroundFactory(new Dirt(), new Lava(), new Fence());

        List<String> end_map = Arrays.asList(
                "%%%%%LLLLLLL%%%%%%%%LLLLLLLLLLLLL%%%%%%%%%%%%%%%%%",
                "%%%%%%%%%%%%%%%%%%LL...........LL%%%%%%%%%%%%%%%%%",
                "%%%%%%%%%%%%%%%LL.................LL%%%%%%%%%%%%%%",
                "%%%%%%%%%%%%%%L.....................L%%%%%%%%%%%%%",
                "%%%%%%%%%%%%%L.......................L%%%%%%%%%%%%",
                "%%%%%%%%%%%%L.........................L%%%%%%%%%%%",
                "%%%%%%%%%%%%L.........................L%%%%%%%%%%%",
                "%%%%%%%%%%%%L......%%%%%...%%%%%......L%%%%%%%%%%%",
                "%%%%%%%%%%%%%....%%%%%%%L.L%%%%%%%....%%%%%%%%%%%%",
                "%%%%%%%%%%%%%...L%%%%%%%L.L%%%%%%%L...%%%%%%%%%%%%",
                "%%%%%%%%%%%%%...L%%%%%%L...L%%%%%%L...%%%%%%%%%%%%",
                "%%%%%%%%%%%%%%%....LL...%%%...LL....%%%%%%%%%%%%%%",
                "%%%%%%%%%%%%%%%%.......%%%%%.......%%%%%%%%%%%%%%%",
                "%%%%%%%%%%%%%%%%%L.......L.......L%%%%%%%%%%%%%%%%",
                "%%%%%%%%%%%%%%%%%%L.%.%.%.%.%.%.L%%%%%%%%%%%%%%%%%",
                "%%%%%%%LLL%%%%%%%%..L.%.%.%.%.L..%%%%%%%LLL%%%%%%%",
                "%%%%%%L....%%%%%%%%.....L.L.L...%%%%%%%L....%%%%%%",
                "%%%%%%%.....LL%%%%%%%.........%%%%%%LL......%%%%%%",
                "%%%%%L...........LL%%%%%%%%%%%%%LLLL..........%%%%",
                "%%%%%....%%%..........LLL%%%LL.........%%%...%%%%%",
                "%%%%%%%%%%%%%%%%%...........LL%%%.%%%%%%%%%%%%%%%%",
                "%%%%%%%%%%%%%%%%LLLL%%%..........LLL%%%%%%%%%%%%%%",
                "%%%%%%%L...LLL.........LL%%%...........LLL...%%%%%",
                "%%%%%%%..........%%%%%%%%%%%%%%%%%...........%%%%%",
                "%%%%%%%%%.....%%%%%%%%%%%%%%%%%%%%%%%%%....%%%%%%%",
                "%%%%%%%%%%...%%%%%%%%%%%%%%%%%%%%%%%%%%....%%%%%%%");

        GameMap final_map = new GameMap(end_groundFactory, end_map);
        world.addGameMap(final_map);

        LavaMap.at(5,0).setGround(new Portal(final_map));
        LavaMap.at(5,0).addActor(new SusToad());
        final_map.addActor(new Bowsette(final_map, LavaMap), final_map.at(27,3));
        final_map.at(25,7).setGround(new Portal(LavaMap.at(4,0), LavaMap));





            world.run();

        }
    }









