package game.positions;

import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.Location;
import game.actions.Jump;
import game.Status;
import game.actors.Goomba;
import game.items.Coin;

/**
 * Class representing Sprout
 */
public class Sprout extends Tree {
    //Sprout class

    private int counter;


    /**
     * Constructor.
     *
     */
    public Sprout(){
        super.setDisplayChar('+');
        counter=0;
        this.registerInstance();

    }
    /**
     * Ground can also experience the joy of time.
     * @param location The location of the Ground
     */
    public void tick(Location location) {
        if (this.hasCapability(Status.RESETTING)){
            double rand = Math.random();
            if (rand < 0.5){
                location.setGround(new Dirt());
            }
            else {
                this.removeCapability(Status.RESETTING);
            }
        }

        counter += 1;
        if (!location.containsAnActor() && Math.random() <= 0.1) {
            location.addActor(new Goomba());
        }
        if (counter%10==0){
            location.setGround(new Sapling());

        }}

    /**
     * Returns an  Action list.
     *
     * @param actor the Actor acting
     * @param location the current Location
     * @param direction the direction of the Ground from the Actor
     * @return an action that can be performed with Sprout
     */
    @Override
    public ActionList allowableActions(Actor actor, Location location, String direction) {
        ActionList actions = new ActionList();
        if(!location.containsAnActor() && !actor.hasCapability(Status.INVINCIBLE)) {
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

    public boolean canActorEnter(Actor actor) {
        return false;

    }

}
