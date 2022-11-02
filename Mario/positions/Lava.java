package game.positions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.positions.Ground;
import edu.monash.fit2099.engine.positions.Location;
import game.Status;

public class Lava extends Ground {

    private Location location;
    //private int counter;
    private GameMap map;

    /**
     * This is the Class that represents the harmful Ground that Players can step onto and lose
     * 15 of their health - and can continue doing so while they remain inside.
     */
    public Lava() {
        super('L');
        //counter = 0;
    }

    @Override
    public void tick(Location location){
        if(location.containsAnActor() && !location.getActor().hasCapability(Status.INVINCIBLE)) {
            location.getActor().hurt(15);
            //System.out.println(location.getActor().isConscious());
            //System.out.println(location.getActor() + " was burnt for 99999 health.");
            if (!location.getActor().isConscious()){
                System.out.println(location.getActor() + " was killed.");
                location.map().removeActor(location.getActor());
            }
        }
        if(location.containsAnActor() && location.getActor().hasCapability(Status.INVINCIBLE)) {
            System.out.println(location.getActor() + " is INVINCIBLE to lava.");
        }


        }


    @Override
    public boolean canActorEnter(Actor actor) {
        if (actor.hasCapability(Status.HOSTILE_TO_ENEMY)){
            return true;
        }
        return false;
    }
}
