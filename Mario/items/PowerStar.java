package game.items;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.DropItemAction;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.Location;
import game.actions.ConsumePowerStarAction;
import game.Status;

/**
 * Class representing PowerStar
 */
public class PowerStar extends Item {
    private int counter;
    private int counterForInvincible;
    private Action action = new ConsumePowerStarAction(this);



    /***
     * Constructor.
     *
     */
    public PowerStar(){
        super("Power Star",'*',true);
        this.addAction(action);
        counter=0;
        counterForInvincible=0;

    }
    /**
     * Inform a carried Item of the passage of time.
     *
     * This method is called once per turn, if the Item is being carried.
     * @param currentLocation The location of the actor carrying this Item.
     * @param actor The actor carrying this Item.
     */
    @Override
    public void tick(Location currentLocation, Actor actor) {
        super.tick(currentLocation, actor);

        if (this.hasCapability(Status.ACTIVE) && counterForInvincible <= 10 && actor.hasCapability(Status.INVINCIBLE)) {
            this.removeAction(action);
            counterForInvincible += 1;
            System.out.println(actor + " is INVINCIBLE " + "for " + (11 - counterForInvincible) + " turns");
        }

        if (counterForInvincible > 10) {
            actor.removeCapability(Status.INVINCIBLE);
            actor.removeCapability(Status.DESTROY_GROUND);
            actor.removeItemFromInventory(this);
        }
    }

    /**
     * Inform an Item on the ground of the passage of time.
     * This method is called once per turn, if the item rests upon the ground.
     * @param currentLocation The location of the ground on which we lie.
     */
    @Override
    public void tick(Location currentLocation) {
        super.tick(currentLocation);
        counter+=1;
        if(counter>=10){
            currentLocation.removeItem(this);
        }

    }
    /**
     * Create and return an action to drop this Item.
     * If this Item is not portable, returns null.
     * @return a new DropItemAction if this Item is portable, null otherwise.
     */
    @Override
    public DropItemAction getDropAction(Actor actor) {
        if(!this.hasCapability(Status.ACTIVE)){
            return new DropItemAction(this);
        }
        return null;
    }
}
