package game.actors;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.displays.Display;
import edu.monash.fit2099.engine.positions.GameMap;
import edu.monash.fit2099.engine.displays.Menu;
import edu.monash.fit2099.engine.weapons.IntrinsicWeapon;
import game.ResetAction;
import game.Resettable;
import game.Status;
import game.magicalfountain.ConsumeWaterAction;
import game.magicalfountain.Water;

/**
 * Class representing the Player.
 */
//player
public class Player extends Actor implements Resettable {
	private IntrinsicWeapon intrinsicWeapon;
	private int damage;

	private final Menu menu = new Menu();
	private Water water;

	/**
	 * Constructor.
	 *
	 * @param name        Name to call the player in the UI
	 * @param displayChar Character to represent the player in the UI
	 * @param hitPoints   Player's starting number of hitpoints
	 */
	public Player(String name, char displayChar, int hitPoints) {
		super(name, displayChar, hitPoints);
		this.addCapability(Status.HOSTILE_TO_ENEMY);
		this.addCapability(Status.RESETTABLE);
		this.registerInstance();
		this.addCapability(Status.OBTAIN_BOTTLE);
		damage=999;

	}

	/**
	 * Figure out what to do next.
	 *
	 * @see Actor#playTurn(ActionList, Action, GameMap, Display)
	 */
	@Override
	public Action playTurn(ActionList actions, Action lastAction, GameMap map, Display display) {
		if (this.hasCapability(Status.RESETTABLE)) {
			actions.add(new ResetAction());
		}

		// Handle multi-turn Actions
		if (lastAction.getNextAction() != null)
			return lastAction.getNextAction();

		if(this.hasCapability(Status.BOTTLE_IN_ITEM)){
			actions.add(new ConsumeWaterAction(water));
		}



		// return/print the console menu
		return menu.showMenu(this, actions, display);
	}

	/**
	 * Gets the char of the player.
	 * @return the current character display
	 */
	@Override
	public char getDisplayChar(){
		return this.hasCapability(Status.TALL) ? Character.toUpperCase(super.getDisplayChar()): super.getDisplayChar();

	}

	/**
	 * Changes the char of the player.
	 * @param charDisplay a char representing the new display of the player
	 */
	public void setCharDisplay(char charDisplay){
		this.setDisplayChar(charDisplay);
	}

	/**
	 * Gets the max health.
	 * @return the player's current max hp
	 */
	public int getMaxHP(){
		int i=getMaxHp();
		return i;
	}

	/**
	 * Creates a weapon for the unarmed Player.
	 * @return an Intrinsic Weapon
	 */
	public IntrinsicWeapon getIntrinsicWeapon() {
		if (this.hasCapability(Status.BASE_ATTACK_DAMAGE_INCREASE)){
			this.removeCapability(Status.BASE_ATTACK_DAMAGE_INCREASE);
			return new IntrinsicWeapon(addDamage(),"jumps");
		}
		return new IntrinsicWeapon(getDamage(), "jumps");
	}


	/**
	 * Reset.
	 */
	@Override
	public void resetInstance() {
		if (this.hasCapability(Status.INVINCIBLE) && this.hasCapability(Status.DESTROY_GROUND)){
			this.removeCapability(Status.INVINCIBLE);
			this.removeCapability(Status.DESTROY_GROUND);

		}

		if (this.hasCapability(Status.JUMP_FREELY) && this.hasCapability(Status.EVOLVE_TO_UPPER_CASE)){
			this.removeCapability(Status.JUMP_FREELY);
			this.removeCapability(Status.EVOLVE_TO_UPPER_CASE);
			setCharDisplay(Character.toLowerCase(getDisplayChar()));
		}

		this.heal(getMaxHP());

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
