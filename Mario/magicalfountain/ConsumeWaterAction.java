package game.magicalfountain;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.weapons.IntrinsicWeapon;
import edu.monash.fit2099.engine.weapons.Weapon;
import game.Status;
import game.actors.Player;

/**
 * Class for ConsumeWaterAction. These represent consume action that the actor can perform.
 */
public class ConsumeWaterAction extends Action {
    private String waterName;
    public int counter;
    private Water water;


    /**
     * Constructor.
     *
     * @param water the water to consume
     */
    public ConsumeWaterAction(Water water){
        this.water=water;
        counter=0;

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

        if(actor.hasCapability(Status.BOTTLE_IN_ITEM)){
            for (Item bottle : actor.getInventory()) {
                if (bottle instanceof Bottle) {
                    int index=((Bottle) bottle).getLastWaterIndex();
                    String currentWater=((Bottle) bottle).getLastWaterString(index);
                    if(currentWater.equals("Healing Water")){
                        actor.heal(50);
                        ((Bottle) bottle).removeWater(index);
                        return actor + " consumes Healing Water from bottle, HP increase by 50";
                    }
                    else if(currentWater.equals("Power Water")){
                        actor.addCapability(Status.BASE_ATTACK_DAMAGE_INCREASE);
                        ((Bottle) bottle).removeWater(index);
                        return actor + " consumes Power Water from bottle, base attack damage increase by 15";

                 }


                }}}


        else{
            if(map.locationOf(actor).getGround().getDisplayChar()=='H'){
                actor.addCapability(Status.DRANK);
                actor.heal(50);
                return actor + " consumes Healing Water directly from fountain, HP increase by 50";
            }
            else if (map.locationOf(actor).getGround().getDisplayChar()=='A'){
                actor.addCapability(Status.DRANK);
                actor.addCapability(Status.BASE_ATTACK_DAMAGE_INCREASE);
              return actor + " consumes Power Water directly from fountain, base attack damage increase by 15";

            }
        }

        return null;}


    /**
     * Returns a descriptive string
     * @param actor The actor performing the action.
     * @return the text we put on the menu
     */
    @Override
    public String menuDescription(Actor actor) {
        if(actor.hasCapability(Status.BOTTLE_IN_ITEM)){
            String ret=actor + " consumes Bottle";
            for (Item bottle : actor.getInventory()) {
                Bottle obj = ((Bottle) bottle);
                ret+=obj.getBottleContent();}
            return ret;

        }

        else{
            String ret=actor + " consumes " + water.getWaterName();
            return ret;
        }



}



    /**
     * get the counter of how many water slots are consumed
     * @param actor The actor performing the action.
     * @return int
     */
    public int getCounter(Actor actor) {
        counter=0;
        if (actor.hasCapability(Status.DRANK)){
            //a sip/drink will automatically consume 2 water slots
            counter+=2;
            return counter;}
        else{
            return counter;

        }

    }
}
