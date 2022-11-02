package game.magicalfountain;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;


/**
 * Class for RefillWaterAction. These represent refill action that the actor can perform.
 */
public class RefillBottleAction extends Action {
    private Water water;
    public int counter;
    private int counterWaterFillInBottle;



    /**
     * Constructor.
     *
     * @param water the water to refill
     */
    public RefillBottleAction(Water water){
        this.water=water;
        counter=0;
        counterWaterFillInBottle=0;


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
        for(Item bottle: actor.getInventory()){
            if (bottle instanceof Bottle){
                if(((Bottle) bottle).getBottleCapacity()<((Bottle) bottle).maxBottleCapacity()){
                    actor.addCapability(Status.REFILLED);
                    ((Bottle) bottle).addWater(water);
                    return water.getWaterName() + " successfully refilled in bottle";
            }
                else{
                    return "Bottle is FULL!!";
                }
        }

    }
        return null;
    }


    /**
     * Returns a descriptive string
     * @param actor The actor performing the action.
     * @return the text we put on the menu
     */
    @Override
    public String menuDescription(Actor actor) {
        return actor + " refill " + water.getWaterName();

    }
    /**
     * get the counter of how many water slots are used
     * @param actor The actor performing the action.
     * @return int
     */
    public int getCounter(Actor actor) {
        counter=0;
        if (actor.hasCapability(Status.REFILLED)){
            //a refill will automatically consume 2 water slots
            counter+=2;
            return counter;}
        else{
            return counter;
        }

    }

}
