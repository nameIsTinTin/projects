package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.weapons.Weapon;

/**
 * Special Action for attacking shells.
 */
public class BreakShellAction extends Action {

    /**
     * The Actor that is to be attacked
     */
    protected Actor target;

    /**
     * The direction of incoming attack.
     */
    protected String direction;


    /**
     * Constructor.
     *
     * @param target the Actor to attack
     */
    public BreakShellAction(Actor target, String direction) {
        this.target = target;
        this.direction = direction;
    }

    /**
     * Allows an actor to attack the target Actor and instantly causes them to be
     * removed off the map.
     *
     * @param actor The actor performing the action.
     * @param map The map the actor is on.
     * @return a String
     */
    @Override
    public String execute(Actor actor, GameMap map) {
        Weapon weapon = actor.getWeapon();

        String result = actor + " " + weapon.verb() + " " + target + "'s shell.";

        ActionList dropActions = new ActionList();
        // drop all items
        for (Item item : target.getInventory())
            dropActions.add(item.getDropAction(actor));
        for (Action drop : dropActions)
            drop.execute(target, map);
        // remove actor
        map.removeActor(target);
        result += System.lineSeparator() + target + " is killed.";

        return result;
    }

    /**
     * Allows the actor to break the shell of the target in the direction in the menu description.
     * @param actor The actor performing the action.
     * @return a String
     */
    @Override
    public String menuDescription(Actor actor) {
        return  actor + " breaks shell of " + target + " at " + direction;
    }
}
