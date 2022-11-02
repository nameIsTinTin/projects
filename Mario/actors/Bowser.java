package game.actors;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.displays.Display;
import edu.monash.fit2099.engine.actions.DoNothingAction;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.positions.Location;
import edu.monash.fit2099.engine.weapons.IntrinsicWeapon;
import game.*;
import game.actions.AttackAction;
import game.AttackBehaviour;
import game.Behaviour;
import game.FollowBehaviour;
import game.items.Key;

import java.util.HashMap;
import java.util.Map;
/**
 * The Great Demon King.
 */
public class Bowser extends Actor implements Resettable {
    private final Map<Integer, Behaviour> behaviours = new HashMap<>(); // priority, behaviour


    /**
     * Constructor.
     */
    public Bowser() {
        super("Bowser", 'B', 500);
        this.addCapability(Status.FIREATTACK);
        this.addItemToInventory(new Key());
        this.registerInstance();
    }

    /**
     * Allows Bowser to be attacked, attack or follow the otherActor.
     * @param otherActor the Actor that might perform an action.
     * @param direction  String representing the direction of the other Actor
     * @param map        current GameMap
     * @return list of actions
     * @see Status#HOSTILE_TO_ENEMY
     */
    @Override
    public ActionList allowableActions(Actor otherActor, String direction, GameMap map) {
        ActionList actions = new ActionList();

        if (otherActor.hasCapability(Status.HOSTILE_TO_ENEMY)) {
            actions.add(new AttackAction(this, direction));
            this.behaviours.put(0, new AttackBehaviour(otherActor));
            this.behaviours.put(1, new FollowBehaviour(otherActor));
        }
        if(otherActor.hasCapability(Status.INVINCIBLE)){
            otherActor.hurt(0);
        }
        return actions;
    }

    /**
     * Figure out what to do next.
     *
     * @see Actor#playTurn(ActionList, Action, GameMap, Display)
     */
    @Override
    public Action playTurn(ActionList actions, Action lastAction, GameMap map, Display display) {
        if (this.hasCapability(Status.RESETTING)){
            this.removeCapability(Status.RESETTING);
            this.heal(500);
            behaviours.clear();
            if (!map.at(29, 10).containsAnActor()){
                map.moveActor(this, map.at(29,10));
            } else {
                map.moveActor(this, map.at(29,9));
            }
        }

        for (Behaviour Behaviour : behaviours.values()) {
            Action action = Behaviour.getAction(this, map);
            if (action != null)
                return action;
        }
        return new DoNothingAction();
    }

    /**
     * Creates a weapon for the unarmed Bowser.
     * @return an Intrinsic Weapon
     */
    @Override
    public IntrinsicWeapon getIntrinsicWeapon() {
        return new IntrinsicWeapon(80, "punches");
    }

    /**
     * Becomes affected by reset.
     */
    @Override
    public void resetInstance() {
        this.addCapability(Status.RESETTING);
    }

}
