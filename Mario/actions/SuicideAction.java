package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;

/**
 * Special Action that causes the Actor to suicide
 */
public class SuicideAction extends Action {

    /**
     * Constructor.
     */
    public SuicideAction() {
    }

    /**
     * Removes an actor from the map.
     * @param actor The actor performing the action.
     * @param map The map the actor is on.
     * @return
     */
    @Override
    public String execute(Actor actor, GameMap map) {
        map.removeActor(actor);
        return menuDescription(actor);
    }

    /**
     * Causes the line to appear in the description that the actor suicided.
     * @param actor The actor performing the action.
     * @return a String
     */
    @Override
    public String menuDescription(Actor actor) {
        return actor + " suicided.";
    }
}
