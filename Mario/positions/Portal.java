package game.positions;

import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.positions.Ground;
import edu.monash.fit2099.engine.positions.Location;
import game.Status;
import game.actions.Teleport;

public class Portal extends Ground {
    /**
     * Constructor.
     *
     * @param map character to display for this type of terrain
     */

    private GameMap gameMap;
    private Location oldLocation;
    public Portal(GameMap map) {
        super('?');
        this.gameMap = map;

    }
    public Portal(Location oldLocation){
        super('?');
        this.oldLocation = oldLocation;
    }


    public Portal(Location oldLocation, GameMap gamemap){
        super('?');
        this.oldLocation = oldLocation;
        this.gameMap = gamemap;
    }

    @Override
    public ActionList allowableActions(Actor actor, Location location, String direction) {
        ActionList actions = new ActionList();
        if(!actor.hasCapability(Status.BEING_JUDGED)) {
            actions.add(new Teleport(this, location, direction, gameMap, oldLocation));
        }
        else{
            actions.add(new Teleport(this, location, direction, gameMap, oldLocation));
        }
        return actions;
    }

    @Override
    public boolean canActorEnter(Actor actor) {
        return false;
    }
}
