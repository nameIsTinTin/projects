package game.positions;

import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.Location;
import game.actions.Jump;
import game.Status;
import game.items.Coin;

/**
 * Class representing Sapling
 */
public class Sapling extends Tree {
    private int counter;

    /**
     * Constructor.
     *
     */
    public Sapling(){
        super.setDisplayChar('t');
        counter=0;
        this.registerInstance();
    }

    /**
     * Returns an  Action list.
     *
     * @param actor the Actor acting
     * @param location the current Location
     * @param direction the direction of the Ground from the Actor
     * @return an action that can be performed with Sapling
     */
    @Override
    public ActionList allowableActions(Actor actor, Location location, String direction) {
        ActionList actions = new ActionList();
        if(location.containsAnActor() == false && !actor.hasCapability(Status.INVINCIBLE)){
            actions.add(new Jump(this, location, direction));
        }
        else{
            location.setGround(new Dirt());
            location.addItem(new Coin(5));
        }
        return actions;
    }

    /**
     * Override this to implement impassable terrain, or terrain that is only passable if conditions are met.
     *
     * @param actor the Actor to check
     * @return false as actor can't enter
     */
    //attempt2ofpush
    public boolean canActorEnter(Actor actor) {
        return false;

    }



    /**
     * Ground can also experience the joy of time.
     * @param location The location of the Ground
     */
    public void tick (Location location){
        if (this.hasCapability(Status.RESETTING)){
            double rand = Math.random();
            if (rand < 0.5){
                location.setGround(new Dirt());
            }
            else {
                this.removeCapability(Status.RESETTING);
            }
        }

        counter+=1;
        if (Math.random() <= 0.1) {
            location.addItem(new Coin(20));
        }
        if(counter%10==0){
            location.setGround(new Mature());
        }
    }


}
