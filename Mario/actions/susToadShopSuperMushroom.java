package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;
import game.items.SuperMushroom;

public class susToadShopSuperMushroom extends Action {

    protected Actor target;

    /**
     *
     * @param actor This is the Actor that is selling the Super Mushroom
     * This class is for the Player to trade with the Suspicious Toad. Specifically, a Super Mushroom
     * for 25 of the Player's health.
     */

    public susToadShopSuperMushroom(Actor actor){
        this.target = actor;
    }

    @Override
    public String execute(Actor actor, GameMap map) {
        actor.hurt(25);
        SuperMushroom superMushroom = new SuperMushroom();
        superMushroom.togglePortability();
        actor.addItemToInventory(superMushroom);
        if(actor.isConscious()) {
            return ("Mmmmmm, finger-licking good ~");
        }
        else{
            map.removeActor(actor);
            return ("A mere hero can only lose so many fingers, right ?");
        }

    }

    @Override
    public String menuDescription(Actor actor) {
        return actor + " sacrifices 25 health for Super Mushroom";
    }
}
