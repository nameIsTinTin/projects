package game.actors;


import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.displays.Display;
import edu.monash.fit2099.engine.actions.DoNothingAction;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.weapons.IntrinsicWeapon;
import game.*;
import game.actions.AttackAction;
import game.actions.SuicideAction;
import game.AttackBehaviour;
import game.Behaviour;
import game.FollowBehaviour;
import game.WanderBehaviour;
import game.magicalfountain.ConsumeBehaviour;
import game.magicalfountain.ConsumeWaterAction;
import game.magicalfountain.HealthFountain;

import java.util.HashMap;
import java.util.Map;
/**
 * A little fungus guy.
 */
//goomba
public class Goomba extends Actor implements Resettable {
	private final Map<Integer, Behaviour> behaviours = new HashMap<>(); // priority, behaviour
	private int damage;

	/**
	 * Constructor.
	 */
	public Goomba() {
		super("Goomba", 'g', 20);
		this.behaviours.put(10, new WanderBehaviour());
		this.registerInstance();
		this.addCapability(Status.CAN_DRINK);
		damage=10;
	}


	/**
	 * Allows the Goomba to be attacked, attack or follow the otherActor.
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

		if(map.contains(this) && this.isConscious()){
			this.behaviours.put(2,new ConsumeBehaviour(this));
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
			map.removeActor(this);
			return new DoNothingAction();
		}

		double rand = Math.random();
		if (rand <= .1){
			return new SuicideAction();
		}

		for (Behaviour Behaviour : behaviours.values()) {
			Action action = Behaviour.getAction(this, map);
			if (action != null)
				return action;
		}
		return new DoNothingAction();
	}

	/**
	 * Creates a weapon for the unarmed Goomba.
	 * @return an Intrinsic Weapon
	 */
	@Override
	public IntrinsicWeapon getIntrinsicWeapon() {
		if (this.hasCapability(Status.BASE_ATTACK_DAMAGE_INCREASE)){
			this.removeCapability(Status.BASE_ATTACK_DAMAGE_INCREASE);
			return new IntrinsicWeapon(addDamage(),"kicks");
		}
		return new IntrinsicWeapon(getDamage(), "kicks");
	}

	/**
	 * Becomes affected by reset.
	 */
	@Override
	public void resetInstance() {
		this.addCapability(Status.RESETTING);
	}

	/**
	 * Increases the base damage of the actor by 15.
	 * @return int that represents the damage value that will be given to the actor
	 */
	public int addDamage(){
		return damage+=15;
	}

	/**
	 * Getter to retrieve the current base attack damage of the actor
	 * @return the current damage value of the actor
	 */
	public int getDamage(){
		return damage;
	}

}
