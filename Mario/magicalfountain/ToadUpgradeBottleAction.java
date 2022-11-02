package game.magicalfountain;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;
import game.items.Coin;
import game.items.SuperMushroom;

/**
 * Class for ToadUpgradeBottleAction. These represent that the toad allow actor to upgrade bottle charges
 */
public class ToadUpgradeBottleAction extends Action {
    protected Actor target;



    /**
     * Constructor.
     *
     * @param actor the actor want to increase bottle charges
     */
    public ToadUpgradeBottleAction(Actor actor){
        this.target=actor;

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

        for (Item bottle : actor.getInventory()) {
            if (bottle instanceof Bottle) {
                ((Bottle) bottle).setBottleCapacity(((Bottle) bottle).maxBottleCapacity()+10);
                actor.removeCapability(Status.SUCCESSFUL_JUMP);
                return actor + " bottle charges increase by 10";
        }}
        return null;}


    /**
     * Returns a descriptive string
     * @param actor The actor performing the action.
     * @return the text we put on the menu
     */
    @Override
    public String menuDescription(Actor actor) {
        return actor + " upgrades bottle charges by 10 after a successful jump on the Wall";
    }
}
