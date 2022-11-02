package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;
import game.items.PowerStar;

public class susToadShopPowerStar extends Action {

    protected Actor target;

    /**
     *
     * @param actor This is the Actor that is selling the Power Star
     * This class is for the Player to trade with the Suspicious Toad. Specifically, a Power Star for 300 of the
     * Player's health. Initially, this is an impossible trade as it involves death but becomes possible as
     * the Player drinks plenty of Fountains.
     */

    public susToadShopPowerStar(Actor actor){
        this.target = actor;
    }

    @Override
    public String execute(Actor actor, GameMap map) {
        actor.hurt(300);
        PowerStar powerStar = new PowerStar();
        powerStar.togglePortability();
        actor.addItemToInventory(powerStar);
        if(actor.isConscious() == false) {
            map.removeActor(actor);
            return("Time to feast upon your lifeless body !");
        }
        else{
            return("IMPOSSIBLE, HOW?!");

        }

    }

    @Override
    public String menuDescription(Actor actor) {
        return actor + " sacrifices 300 health for Power Star";
    }
}
