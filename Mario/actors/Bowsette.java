package game.actors;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actions.DoNothingAction;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.displays.Display;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.weapons.IntrinsicWeapon;
import edu.monash.fit2099.engine.weapons.WeaponItem;
import game.AttackBehaviour;
import game.Behaviour;
import game.FollowBehaviour;
import game.Status;
import game.actions.AttackAction;
import game.items.Coin;
import game.items.Essence;
import game.magicalfountain.ConsumeBehaviour;
import game.positions.Portal;

import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Bowsette extends Actor {
    private final Map<Integer, Behaviour> behaviours = new HashMap<>(); // priority, behaviour
    private GameMap currentmap;
    private GameMap oldmap;

    /**
     *
     * @param currentmap This is the Map that Bowsette spawns into
     * @param oldmap This is the Map that Mario has previously left to enter into Bowsette's spawn
     * This Class represents the hidden enemy "Bowsette", who's a stronger (and prettier!) version of Bowser
     * who has the same movesets as Bowser. The core differences is Bowsette debuffs the Player from leaving without
     * defeating Bowsette and Bowsette can drop an Essence of Armaggedon which they can submit to Toad for power.
     *
     */
    public Bowsette(GameMap currentmap, GameMap oldmap) {
        super("Bowsette", '♡', 666);
        this.addCapability(Status.FIREATTACK);
        this.addCapability(Status.BEING_JUDGED);
        this.currentmap = currentmap;
        this.oldmap = oldmap;
        this.addItemToInventory(new Essence());

    }

    @Override
    public ActionList allowableActions(Actor otherActor, String direction, GameMap map) {
        ActionList actions = new ActionList();
        Random random = new Random();


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

    @Override
    public IntrinsicWeapon getIntrinsicWeapon() {
        return new IntrinsicWeapon(1, "bashes skull of");
    }

    @Override
    public Action playTurn(ActionList actions, Action lastAction, GameMap map, Display display) {
        for (Behaviour Behaviour : behaviours.values()) {
            Action action = Behaviour.getAction(this, map);
            if (action != null)
                return action;
        }
        return new DoNothingAction();
    }

    }

