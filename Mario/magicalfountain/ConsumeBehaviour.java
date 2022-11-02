package game.magicalfountain;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Behaviour;
import game.Status;

/**
 * A class that figures out when should the actor consumes water
 */
public class ConsumeBehaviour implements Behaviour {

    /**
     * Constructor.
     */
    public ConsumeBehaviour(Actor actor){};

    /**
     * Returns a ConsumeAction
     * If actor is on Health Fountain, the actor will be consuming Healing Water
     * If actor is on Power Fountain, the actor will be consuming Power Water
     * @param actor the Actor enacting the behaviour
     * @param map the map that actor is currently on
     * @return an Action, or null if no ConsumeWaterAction is possible
     */
    @Override
    public Action getAction(Actor actor, GameMap map) {

        if(map.locationOf(actor).getGround().getDisplayChar()=='H' && actor.hasCapability(Status.CAN_DRINK)){
            return new ConsumeWaterAction(new Water("Healing Water"));
        }
        if(map.locationOf(actor).getGround().getDisplayChar()=='A' && actor.hasCapability(Status.CAN_DRINK)){
            return new ConsumeWaterAction(new Water("Power Water"));}


        return null;


    }
}
