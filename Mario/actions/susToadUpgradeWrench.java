package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.items.Wrench;

public class susToadUpgradeWrench extends Action {

    int old_damage;
    int new_damage;
    protected Actor target;

    /**
     *
     * @param actor This is the Actor who's upgrading the Wrench
     * This class is crucial to the Player who wishes to upgrade the amount of damage they deal. This allows the
     * Player to trade 40 of their current health for Suspicious Toad to upgrade their weapon for an additional
     * number from 0 to 40.
     */

    public susToadUpgradeWrench(Actor actor){
        this.target = actor;
    }

    @Override
    public String execute(Actor actor, GameMap map) {
        actor.hurt(40);
        if(actor.isConscious()) {
            for (Item wrench : actor.getInventory()) {
                if (wrench instanceof Wrench) {
                    old_damage = ((Wrench) wrench).getCurrent_damage();
                    actor.removeItemFromInventory(wrench);
                    new_damage = ((Wrench) wrench).upgradeWrench();
                    Wrench refined_wrench = new Wrench(old_damage + new_damage);
                    refined_wrench.togglePortability();
                    actor.addItemToInventory(refined_wrench);
                    return("A fine wrench for mediocrity.... " + "\n" +
                            "New Damage: (OLD) " + old_damage + " + (GAINED) " + new_damage + " = " + (old_damage+new_damage));
                }}
            return ("Seems like there was no Wrench on you, sweet boy. I'll still take off some flesh though :)");
        }
        else{
            map.removeActor(actor);
            return("Oh sweet brother, another skull has been caved in by my own Wrench");
        }

    }

    @Override
    public String menuDescription(Actor actor) {
        return actor + " sacrifices 40 health for an upgraded Wrench";
    }
}
