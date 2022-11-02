package game.magicalfountain;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;
/**
 * Class for ToadGiveBottleAction. These represent that the toad can give bottle to actor
 */

public class ToadGiveBottleAction extends Action {
    protected Actor target;


    /**
     * Constructor.
     *
     * @param actor the actor to give
     */
    public ToadGiveBottleAction(Actor actor){
        this.target = actor;
    }

    /**
     * Perform the Action.
     *
     * @param actor The actor performing the action.
     * @param map The map the actor is on.
     * @return a description of what happened that can be displayed to the user.
     */
    @Override
    public String execute(Actor actor, GameMap map) {
        if(actor.hasCapability(Status.OBTAIN_BOTTLE)){
            actor.addItemToInventory(new Bottle());
            actor.addCapability(Status.BOTTLE_IN_ITEM);
            actor.removeCapability(Status.OBTAIN_BOTTLE);
            return "Bottle in " + actor + "'s inventory";}
        return null;

        }


    /**
     * Returns a descriptive string
     * @param actor The actor performing the action.
     * @return the text we put on the menu
     */
    @Override
    public String menuDescription(Actor actor) {
        return actor + " obtain the bottle";
    }
}
