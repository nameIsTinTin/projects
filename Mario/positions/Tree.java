package game.positions;

import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.Ground;
import edu.monash.fit2099.engine.positions.Location;
import game.Resettable;
import game.Status;
import game.actors.Goomba;

public class Tree extends Ground implements Resettable {
    /**
     * A counter for growth.
     */
    private int counter;

    /**
     * Constructor.
     *
     */
    public Tree() {
        super('+');
        this.registerInstance();
    }

    /**
     * Tree can also experience the joy of time.
     * @param location The location of the Tree
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
        }
    }

    /**
     * Determine whether an actor is able to travel on this ground.
     * @param actor the Actor to check
     * @return a boolean representing whether an actor can move on this ground.
     */
    public boolean canActorEnter(Actor actor) {
        if (actor.hasCapability(Status.FLYING)) {
            return true;
        }
        return false;
    }

    /**
     * Becomes affected by reset.
     */
    @Override
    public void resetInstance() {
        this.addCapability(Status.RESETTING);
    }
}