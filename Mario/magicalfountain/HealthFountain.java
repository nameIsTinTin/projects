package game.magicalfountain;

import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.Ground;
import edu.monash.fit2099.engine.positions.Location;
import edu.monash.fit2099.engine.weapons.Weapon;
import game.Status;

import java.util.ArrayList;
//health fountain

/**
 * Class representing the HealthFountain
 */
public class HealthFountain extends Ground {
    private int waterCapacity;
    private Actor actorOne;
    private int maxWaterCapacity;
    private ActionList actions;
    private ConsumeWaterAction consumeWaterAction;
    private RefillBottleAction refillBottleAction;
    private int turn;

    /**
     * Constructor.
     */
    public HealthFountain() {
        super('H');
        maxWaterCapacity=10;
        waterCapacity=10;
        consumeWaterAction=new ConsumeWaterAction(new Water("Healing Water"));
        refillBottleAction=new RefillBottleAction(new Water("Healing Water"));
        turn=0;


    }

    /**
     * Returns an Action List that the actor are allowed to perform on health fountain.
     *
     * @param actor the Actor acting
     * @param location the current Location
     * @param direction the direction of the Ground from the Actor
     * @return Action List that the actor are allowed to perform
     */
    @Override
    public ActionList allowableActions(Actor actor, Location location, String direction) {
        this.actorOne=actor;
        actions=new ActionList();

        //for player
        if (location.containsAnActor()&& !actor.hasCapability(Status.CAN_DRINK)){
            if(actor.hasCapability(Status.BOTTLE_IN_ITEM) && waterCapacity!=0){

                actions.add(refillBottleAction);
            }
            else if(!actor.hasCapability(Status.BOTTLE_IN_ITEM) && waterCapacity!=0){
                actions.add(consumeWaterAction);

            }
        }
        else if (location.containsAnActor()&& actor.hasCapability(Status.CAN_DRINK) && waterCapacity!=0){
            actions.add(consumeWaterAction);
        }



      return actions;
    }
    /**
     * Ground can also experience the joy of time.
     * @param location The location of the Ground
     */

    @Override
    public void tick(Location location) {
        super.tick(location);
        int counterOfWaterConsumed = consumeWaterAction.getCounter(actorOne);
        int counterOfWaterRefilled = refillBottleAction.getCounter(actorOne);
        if (location.containsAnActor() && waterCapacity != 0) {
            waterCapacity = waterCapacity - counterOfWaterConsumed;
            actorOne.removeCapability(Status.DRANK);

            if (actorOne.hasCapability(Status.BOTTLE_IN_ITEM)) {
                waterCapacity = waterCapacity - counterOfWaterRefilled;
                actorOne.removeCapability(Status.REFILLED);
            }
        System.out.println(actorOne + " refills/consumes water from Health Fountain " + "(" + waterCapacity + "/" + maxWaterCapacity + ")");}

        else if(waterCapacity==0){
            if(actorOne.hasCapability(Status.CAN_DRINK)){
                actions.remove(consumeWaterAction);
                actorOne.removeCapability(Status.CAN_DRINK);
            }
            else{
                actions.remove(refillBottleAction);
            }
            System.out.println("No water left, water will be refilled in " + turn + "/5 turns remaining");
            turn++;
            if(turn%5==0 && actorOne.hasCapability(Status.BOTTLE_IN_ITEM)){
                waterCapacity=maxWaterCapacity;
                actions.add(refillBottleAction);
            }
            else if(turn%5==0 && !actorOne.hasCapability(Status.BOTTLE_IN_ITEM)){
                waterCapacity=maxWaterCapacity;
                actions.add(consumeWaterAction);
                actorOne.addCapability(Status.CAN_DRINK);
            }
        }

    }
}


