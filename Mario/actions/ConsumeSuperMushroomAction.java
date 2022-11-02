
package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;
import game.actors.Player;
import game.items.SuperMushroom;


/**
 * Class for ConsumeSuperMushroomAction. These represent things that the actor can do.
 */
public class ConsumeSuperMushroomAction extends Action  {

    private final SuperMushroom superMushroom;

    /**
     * Constructor.

     */
    public ConsumeSuperMushroomAction(SuperMushroom superMushroom){
        this.superMushroom = superMushroom;
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
        for (Item superMushroom : actor.getInventory()){
            if (superMushroom instanceof SuperMushroom){
                actor.addCapability(Status.EVOLVE_TO_UPPER_CASE);
                actor.addCapability(Status.JUMP_FREELY);
                Player actor1 = (Player) actor;
                actor1.setCharDisplay(Character.toUpperCase(actor.getDisplayChar()));
                actor.increaseMaxHp(50);
                actor.removeItemFromInventory(superMushroom);
                System.out.println(actor + " max HP increased by 50");
                return actor + " max HP increased by 50";
            }
        }
        actor.addCapability(Status.EVOLVE_TO_UPPER_CASE);
        actor.addCapability(Status.JUMP_FREELY);
        Player actor1 = (Player) actor;
        actor1.setCharDisplay(Character.toUpperCase(actor.getDisplayChar()));
        actor.increaseMaxHp(50);
        map.locationOf(actor).removeItem(superMushroom);
        System.out.println(actor + " max HP increased by 50");
        return actor + "'s max HP = " + ((Player) actor).getMaxHP();
    }




    /**
     * Returns a descriptive string
     * @param actor The actor performing the action.
     * @return the text we put on the menu
     */

    @Override
    public String menuDescription(Actor actor) {
        return actor + " consumes the Super Mushroom";
    }


}










