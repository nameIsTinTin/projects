package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;
import game.items.Essence;
import game.items.Wrench;

import java.nio.channels.AcceptPendingException;

public class toadUpgradeMario extends Action {

    Actor target;
    Boolean containsEssence = false;

    /**
     *
     * @param target This is the Actor that's providing the upgrade to Mario
     * This class is ultimately the most rewarding yet most difficult quest that Mario can achieve. This class
     * allows the Player to trade an Essence, an Item dropped from Bowsette, for a ridiculously high damage
     * dealing Wrench and an insanely high amount of HP gain.
     */
    public toadUpgradeMario(Actor target){

        this.target = target;
    }

    @Override
    public String execute(Actor actor, GameMap map) {

        for(Item item: actor.getInventory()){
            if(item instanceof Essence){
                containsEssence = true;
            }
        }
        if(containsEssence) {
            for (int i = 0; i < actor.getInventory().size(); i++) {
                actor.removeItemFromInventory(actor.getInventory().get(i));
            }
            Wrench gold_wrench = new Wrench(99999);
            gold_wrench.togglePortability();
            actor.addItemToInventory(gold_wrench);
            actor.increaseMaxHp(9999);
            actor.heal(9999);
            actor.addCapability(Status.GOD);
            return ("The finest of Wrenches, for the finest plumber among them all" + "\n"
                    + "The Essence has combined with you, now you're practically indestructible!");
        }
        else{
            return ("Uh oh...seems like you've forgotten to pick up something important");
        }
    }

    @Override
    public String menuDescription(Actor actor) {
        return actor + " gives Essence of Armageddon";
    }
}
