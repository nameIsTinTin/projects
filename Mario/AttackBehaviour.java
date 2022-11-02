package game;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.positions.Location;
import game.actions.AttackAction;

/**
 * A class that figures out an Action that will attack the
 * target Actor.
 */
public class AttackBehaviour implements Behaviour {

    /**
     * The target to attack.
     */
    private final Actor target;

    /**
     * Constructor.
     *
     * @param subject the Actor to attack
     */
    public AttackBehaviour(Actor subject) {
        this.target = subject;
    }

    /**
     * Returns an Action that causes the Actor to attack the target.
     * If either actor doesn't exist or not in range, returns null
     *
     * @param actor the Actor enacting the behaviour
     * @param map the GameMap containing the Actor
     * @return an Action, or null if no Action is possible
     */
    @Override
    public Action getAction(Actor actor, GameMap map) {
        if(!map.contains(target) || !map.contains(actor))
            return null;

        Location here = map.locationOf(actor);
        Location there = map.locationOf(target);

        int currentDistance = distance(here, there);
        if (currentDistance <= 2){
            Action attack = new AttackAction(target);
            return attack;
        }

        return null;
    }

    /**
     * Compute the Manhattan distance between two locations.
     *
     * @param a the first location
     * @param b the first location
     * @return the number of steps between a and b if you only move in the four cardinal directions.
     */
    private int distance(Location a, Location b) {
        return Math.abs(a.x() - b.x()) + Math.abs(a.y() - b.y());
    }

}
