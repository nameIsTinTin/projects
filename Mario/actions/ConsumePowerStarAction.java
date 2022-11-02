
package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;
import game.items.PowerStar;

/**
 * Class for ConsumePowerStarAction. These represent things that the actor can do.
 */
public class ConsumePowerStarAction extends Action {
    private PowerStar powerStar;
    private int counter;

    /**
     * Constructor.

     */
    public ConsumePowerStarAction(PowerStar powerStar){
        this.powerStar=powerStar;
        counter=10;

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
        for (Item powerStar : actor.getInventory()) {
            if (powerStar instanceof PowerStar) {
                actor.heal(200);
                actor.addCapability(Status.INVINCIBLE);
                actor.addCapability(Status.DESTROY_GROUND);
                powerStar.addCapability(Status.ACTIVE);
                return actor + " consumed Power Star";
            }

        }

        actor.heal(200);
        actor.addCapability(Status.INVINCIBLE);
        actor.addCapability(Status.DESTROY_GROUND);
        map.locationOf(actor).removeItem(powerStar);
        actor.addItemToInventory(powerStar);
        powerStar.addCapability(Status.ACTIVE);
        return actor + " consumed Power Star";
    }





    /**
     * Returns a descriptive string
     * @param actor The actor performing the action.
     * @return the text we put on the menu
     */
    @Override
    public String menuDescription(Actor actor) {
        return actor.toString() + " consumes the Power Star - " + counter-- + " turns remaining";
    }


}
