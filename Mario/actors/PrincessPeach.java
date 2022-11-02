package game.actors;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actions.DoNothingAction;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.displays.Display;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.actions.EndGameAction;
import game.items.Key;
import game.Status;

/**
 * Princess Peach.
 */
public class PrincessPeach extends Actor {

    /**
     * Constructor.
     */
    public PrincessPeach() {
        super("Princess Peach", 'P', 9999);
    }

    /**
     * Allows Peach to interact with the player.
     * @param otherActor the Actor that might be performing the action
     * @param direction  String representing the direction of the other Actor
     * @param map        current GameMap
     * @return list of actions
    */

    @Override
    public ActionList allowableActions(Actor otherActor, String direction, GameMap map) {
        ActionList actions = new ActionList();

        if(otherActor.hasCapability(Status.HOSTILE_TO_ENEMY)) {
            for (Item items : otherActor.getInventory()){
                if (items instanceof Key){
                    actions.add(new EndGameAction(this));
                }
            }
        }
        return actions;
    }


    /**
     * Figure out what to do next.
     *
     * @see Actor#playTurn(ActionList, Action, GameMap, Display)
     */
    @Override
    public Action playTurn(ActionList actions, Action lastAction, GameMap map, Display display) {
        return new DoNothingAction();

    }

}