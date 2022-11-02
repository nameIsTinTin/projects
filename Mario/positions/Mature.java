package game.positions;

import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.Exit;
import edu.monash.fit2099.engine.positions.Location;
import game.actions.Jump;
import game.Status;
import game.actors.FlyingKoopa;
import game.actors.Koopa;
import game.items.Coin;

public class Mature extends Tree {
    private int counter;



    /**
     * Class representing Mature
     */
    public Mature(){
        super.setDisplayChar('T');
        counter=0;
        this.registerInstance();
    }


    /**
     * Returns an  Action list.
     *
     * @param actor the Actor acting
     * @param location the current Location
     * @param direction the direction of the Ground from the Actor
     * @return an action that can be performed with Mature
     */
    //attempt2ofpush
    @Override
    public ActionList allowableActions(Actor actor, Location location, String direction) {
        ActionList actions = new ActionList();
        if(location.containsAnActor() == false) {
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

    /**
     * Ground can also experience the joy of time.
     * @param location The location of the Ground
     */

    public void tick(Location location){
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
        /**
        if(!location.containsAnActor() && Math.random() <= 0.15){
            location.addActor(new Koopa());
        }
         */
        if(!location.containsAnActor() && Math.random() <= 0.075){
            location.addActor(new FlyingKoopa());}
        else if(!location.containsAnActor() && Math.random() <= 0.15){
            location.addActor(new Koopa());
        }


        if(counter % 5 == 0){
            boolean grow=false;
            for (Exit exit: location.getExits()){
                if (exit.getDestination().getGround().hasCapability(Status.FERTILE) && Math.random()<0.125 && grow==false){
                    exit.getDestination().setGround(new Sprout());
                    grow=true;

                }
            }

        }
        if(Math.random()<=0.2){
            location.setGround(new Dirt());
        }


    }


}
