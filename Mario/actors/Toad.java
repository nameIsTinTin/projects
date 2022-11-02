package game.actors;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actions.DoNothingAction;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.displays.Display;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.*;
import game.actions.*;
import game.items.Essence;
import game.items.Wrench;
import game.magicalfountain.ToadGiveBottleAction;
import game.magicalfountain.ToadUpgradeBottleAction;
import game.magicalfountain.ToadGiveBottleAction;

import javax.swing.plaf.synth.SynthTableUI;
//toad

/**
 * A toad guy.
 */
public class Toad extends Actor {

    /**
     * Constructor.
     */

    Boolean containsEssence = false;
    public Toad() {
        super("Toad", 'O', 9999);
    }


    /**
     * Allows Toad to interact with the player, to talk or to purchase items.
     * @param otherActor the Actor that might be performing attack
     * @param direction  String representing the direction of the other Actor
     * @param map        current GameMap
     * @return list of actions
     */


    @Override
    public ActionList allowableActions(Actor otherActor, String direction, GameMap map) {
        ActionList actions = new ActionList();
        for(Item item : otherActor.getInventory()){
            if(item instanceof Essence){
                containsEssence = true;
            }
        }

        if(otherActor.hasCapability(Status.HOSTILE_TO_ENEMY)) {
            actions.add(new toadShopPowerStar(this));
            actions.add(new toadShopSuperMushroom(this));
            actions.add((new toadShopWrench(this)));
            actions.add(new toadSpeakAction(this));

        }
        if(!otherActor.hasCapability(Status.BOTTLE_IN_ITEM)){
            actions.add(new ToadGiveBottleAction(this));
        }
        if(otherActor.hasCapability(Status.SUCCESSFUL_JUMP) && otherActor.hasCapability(Status.BOTTLE_IN_ITEM)){
            actions.add(new ToadUpgradeBottleAction(this));
        }

        if(otherActor.hasCapability(Status.LIBERATED) && !otherActor.hasCapability(Status.GOD)) {
            actions.add(new toadUpgradeMario(this));}

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
