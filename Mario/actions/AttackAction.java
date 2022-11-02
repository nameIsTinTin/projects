package game.actions;

import java.util.Random;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.weapons.Weapon;
import game.Status;
import game.actors.Player;
import game.positions.Fire;

/**
 * Special Action for attacking other Actors.
 */
public class AttackAction extends Action {

	/**
	 * The Actor that is to be attacked
	 */
	protected Actor target;

	/**
	 * The direction of incoming attack.
	 */
	protected String direction;

	/**
	 * Random number generator
	 */
	protected Random rand = new Random();

	/**
	 * Constructor.
	 * 
	 * @param target the Actor to attack
	 * @param direction the direction to attack
	 */
	public AttackAction(Actor target, String direction) {
		this.target = target;
		this.direction = direction;
	}

	/**
	 * Constructor.
	 * @param target the Actor to attack
	 */
	public AttackAction(Actor target) {
		this.target = target;
	}

	/**
	 * Allows an actor to attack the target Actor.
	 *
	 * @param actor The actor performing the action.
	 * @param map The map the actor is on.
	 * @return a String
	 */
	@Override
	public String execute(Actor actor, GameMap map) {

		Weapon weapon = actor.getWeapon();

		//Attacking enemies. When active, a successful attack will instantly kill enemies.
		if(rand.nextInt(100)<= weapon.chanceToHit() && actor.hasCapability(Status.INVINCIBLE)){
			if(target.hasCapability(Status.DORMANTABLE)){
				target.hurt(999999999);
				return target + " go to a dormant state";}
			else{
				map.removeActor(target);
				return target + " is killed.";

			}

		}
		//The effect will last until it receives any damage (e.g., hit by the enemy). Once the effect wears off,
		// the display character returns to normal (lowercase)
		if(rand.nextInt(100)<= weapon.chanceToHit() && target.hasCapability(Status.EVOLVE_TO_UPPER_CASE)){
			Player target1 = (Player) target;
			target1.setCharDisplay(Character.toLowerCase(target1.getDisplayChar()));
			target.removeCapability(Status.EVOLVE_TO_UPPER_CASE);
			target.removeCapability(Status.JUMP_FREELY);
		}


		if (!(rand.nextInt(100) <= weapon.chanceToHit())) {
			return actor + " misses " + target + ".";
		}

		int damage = weapon.damage();
		String result = actor + " " + weapon.verb() + " " + target + " for " + damage + " damage.";
		target.hurt(damage);

		if (actor.hasCapability(Status.FIREATTACK)){
			map.locationOf(target).setGround(new Fire());
		}



		if (!target.isConscious() && !target.hasCapability(Status.DORMANTABLE)) {
			ActionList dropActions = new ActionList();
			// drop all items
			for (Item item : target.getInventory())
				dropActions.add(item.getDropAction(actor));
			for (Action drop : dropActions)
				drop.execute(target, map);
			if(actor.hasCapability(Status.BEING_JUDGED)){
				actor.removeCapability(Status.BEING_JUDGED);
				actor.addCapability(Status.LIBERATED);
				System.out.println("YOUR SOUL IS LIBERATED");
			}
			// remove actor
			map.removeActor(target);
			result += System.lineSeparator() + target + " is killed.";
			}
		return result;
	}

	/**
	 * Allows the actor to attack the target in the direction in the menu description.
	 * @param actor The actor performing the action.
	 * @return a String
	 */
	@Override
	public String menuDescription(Actor actor) {
		return actor + " attacks " + target + " at " + direction;
	}
}
