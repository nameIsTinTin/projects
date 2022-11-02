package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.actors.ActorLocationsIterator;
import edu.monash.fit2099.engine.positions.*;
import game.Status;
import game.actors.SusToad;
import game.actors.Toad;
import game.positions.*;

public class Teleport extends Action {

    protected Ground highground;
    protected Location location;
    protected Location oldLocation;
    protected String direction;
    protected GameMap gameMap;
    private GameMap mapReference;


    public Teleport(Ground highground, Location location, String direction, GameMap gameMap, Location oldLocation) {
        this.highground = highground; //The Warp Pipe we're teleporting into
        this.location = location; //The Location of the Warp Pipe we're entering into
        this.direction = direction; //The Direction of the Warp Pipe we're entering into
        this.gameMap = gameMap; //The Game Map of the Warp Pipe we're entering out of
        this.oldLocation = oldLocation; //The location of the Warp Pipe that sent Mario into the map he's inside now
    }

    @Override
    public String execute(Actor actor, GameMap map) {

        if (highground.getDisplayChar() == '?' && !actor.hasCapability(Status.LIBERATED)){ //To intiate the final boss
            if (actor.hasCapability(Status.BEING_JUDGED)){
                return("TRYING TO RUN AWAY, MARIO ?!");
            }
            actor.addCapability(Status.BEING_JUDGED);
            gameMap.moveActor(actor, gameMap.at(17,3));
            return("Mario feels fear for the first time.");
        }
        if (highground.getDisplayChar() == '?' && actor.hasCapability(Status.LIBERATED)){
            gameMap.at(5,0).setGround(new Dirt());
            gameMap.moveActor(actor, oldLocation);
            return("Mario feels free.");
        }

        if (map.isAnActorAt(map.at(44, 11))) { //To initiate lava world
            gameMap.at(0, 0).setGround(new WarpPipe(location, map));
            if(gameMap.isAnActorAt(gameMap.at(5,0))){
                SusToad presence = new SusToad();
                presence.personSpeaking();
            }
            gameMap.moveActor(actor, gameMap.at(0, 0));
            return ("Quite the weather here");


        } else {
            gameMap.moveActor(actor, gameMap.at(oldLocation.x(), oldLocation.y())); //To return back to original world
            return ("We're back !!");
        }

    }


    @Override
    public String menuDescription(Actor actor) {
        if (location.map().isAnActorAt(location.map().at(44,11))) {
            return "Teleport to Lava Zone using Warp Pipe at " + direction + "(" + location.x() + "," + location.y() + ")";
        }

        if(actor.hasCapability(Status.LIBERATED) && !oldLocation.map().isAnActorAt(oldLocation.map().at(44,11))){
            return "Teleport back to Lava Zone using Mysterious Portal at " + direction + "(" + location.x() + "," + location.y() + ")";
        }

        if (highground.getDisplayChar() == '?' && !actor.hasCapability(Status.LIBERATED)){
            return "Teleport to Judgement Day using Mysterious Portal " + direction + "(" + location.x() + "," + location.y() + ")";
        }
        else {
            return "Teleport to Original World using Warp Pipe at " + direction + "(" + location.x() + "," + location.y() + ")";
        }
    }
}
