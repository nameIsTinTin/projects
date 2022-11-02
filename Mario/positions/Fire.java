package game.positions;

import edu.monash.fit2099.engine.positions.Ground;
import edu.monash.fit2099.engine.positions.Location;
import game.Status;

/**
 * A class that represents the burning ground.
 */
public class Fire extends Ground {
    Location location;
    int counter;

    public Fire() {
        super('v');
    }

    @Override
    public void tick(Location location) {
        if (counter == 3){
        location.setGround(new Dirt());
        }
        counter += 1;

        if (location.containsAnActor()){
            location.getActor().hurt(20);
            System.out.println(location.getActor() + " was burnt for 20 health.");
            if (!location.getActor().isConscious()) {
                System.out.println(location.getActor() + " was killed.");
                location.map().removeActor(location.getActor());
            }
        }

        if(location.containsAnActor() && location.getActor().hasCapability(Status.INVINCIBLE)) {
            System.out.println(location.getActor() + " is INVINCIBLE to fire.");
        }
    }

}