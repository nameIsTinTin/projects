package game;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.DoNothingAction;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;


/**
 * A class that causes an actor to do nothing.
 */
public class DormantBehaviour implements Behaviour {

    /**
     * Returns an Action to do nothing.
     * @param actor the Actor enacting the behaviour
     * @param map the GameMap containing the Actor
     * @return an Action
     */
    public Action getAction(Actor actor, GameMap map){
        return new DoNothingAction();
        }
}
