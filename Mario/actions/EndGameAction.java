package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;

/**
 * Special action that causes the game to end.
 */
public class EndGameAction extends Action {

    /**
     * The Actor that is to be talked to.
     */
    protected Actor target;

    /**
     * Constructor.
     */
    public EndGameAction(Actor target){
        this.target = target;
    }

    /**
     * Removes the main actor from the map.
     * @param actor The actor performing the action.
     * @param map The map the actor is on.
     * @return a string that represents the victory screen.
     */
    @Override
    public String execute(Actor actor, GameMap map) {
        System.out.println(actor + " has successfully saved the Mushroom Kingdom!");
        map.removeActor(actor);
        return ""; // shouldn't matter what it says here
    }

    /**
     * Allows the actor to interact with the target to end the game in the menu description.
     * @param actor The actor performing the action.
     * @return a String
     */
    @Override
    public String menuDescription(Actor actor) {
        return actor + " uses the key to free " + target + ".";
    }
}
