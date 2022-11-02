
package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.*;
import edu.monash.fit2099.engine.positions.*;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;
import game.actors.Player;
import game.positions.*;


import java.util.Random;

import static java.lang.Integer.parseInt;
//Attempting to push again
//jump updated

public class Jump extends Action {


    protected Ground highground;
    protected Location location;
    protected String directions;
    protected ActionList actions;
    protected GameMap map;
    protected ActorLocationsIterator actorsLocation;



    public Jump(Ground highground, Location location, String direction) {
        this.highground = highground;
        this.location = location;
        this.directions = direction;
    }


    @Override
    public String execute(Actor actor, GameMap map) {


        if (highground.canActorEnter(actor) == false) {

            if(highground.getClass() == WarpPipe.class){
                map.moveActor(actor, location);
                return ("Successful Jump on Warp Pipe!");
            }

            if (highground.getClass() == Mature.class) {
                int Maturefail = new Random().nextInt(7);

                //when superMushroom is consumed
                if (actor.hasCapability(Status.JUMP_FREELY)) {
                    map.moveActor(actor, location);
                    return ("Successful Jump on Mature at " + directions + "(consumed Super Mushroom)");

                } else if (Maturefail >= 2) {
                    actor.hurt(30);
                    return ("OUCH, 30 damage received!");
                } else {
                    map.moveActor(actor, location);
                    return ("Successful Jump on Mature at " + directions);
                }
            }

            if (highground.getClass() == Sapling.class) {
                boolean Saplingfail = new Random().nextInt(5) == 0;

                //when superMushroom is consumed
                if (actor.hasCapability(Status.JUMP_FREELY)) {
                    map.moveActor(actor, location);
                    return ("Successful Jump on Sapling at " + directions + "(consumed Super Mushroom)");

                } else if (Saplingfail == true) {
                    actor.hurt(20);
                    return ("Ouch, 20 damage received!");
                } else {
                    map.moveActor(actor, location);
                    return ("Successful Jump on Sapling at " + directions);
                }

            }


            if (highground.getClass() == Wall.class) {
                boolean Wallfail = new Random().nextInt(5) == 0;

                //when superMushroom is consumed
                if (actor.hasCapability(Status.JUMP_FREELY)) {
                    map.moveActor(actor, location);
                    actor.addCapability(Status.SUCCESSFUL_JUMP);
                    return ("Successful Jump on Wall at " + directions + "(consumed Super Mushroom)");

                } else if (Wallfail == true) {
                    actor.hurt(20);
                    return ("Ouch, 20 damage received!");
                } else {
                    map.moveActor(actor, location);
                    actor.addCapability(Status.SUCCESSFUL_JUMP);
                    return ("Successful Jump on Wall at " + directions);
                }

            }

            if (highground.getClass() == Sprout.class) {
                boolean Sproutfail = new Random().nextInt(10) == 0;

                //when superMushroom is consumed
                if (actor.hasCapability(Status.JUMP_FREELY)) {
                    map.moveActor(actor, location);
                    return ("Successful Jump on Sprout at " + directions + "(consumed Super Mushroom)");

                } else if (Sproutfail == true) {
                    actor.hurt(10);
                    return ("ouch, 10 damage received!");
                } else {
                    map.moveActor(actor, location);
                    return ("Successful Jump on Sprout at " + directions);
                }
            }

        }

        return ("TEST");
    }


    @Override
    public String menuDescription(Actor actor) {
        if(highground.getClass() == WarpPipe.class){
            return (actor + " jumps on Warp Pipe by " + directions + "(" + location.x() + "," + location.y() + ")");
        }
        return (actor + " jumps on " + highground.getClass().getCanonicalName().substring(15) + " by " + directions + "(" + location.x() + "," + location.y() + ")");
        }
    }







