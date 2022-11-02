package game.positions;

import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.Ground;


/**
 * A class that represents the floor inside a building.
 */
public class Fence extends Ground {
    public Fence() {
        super('%');
    }

    @Override
    public boolean canActorEnter(Actor actor) {
        return false;
    }
}