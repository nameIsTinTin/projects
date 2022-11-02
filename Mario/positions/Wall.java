package game.positions;

import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.Ground;
import edu.monash.fit2099.engine.positions.Location;
import game.actions.Jump;
import game.Status;
import game.items.Coin;

public class Wall extends Ground {

	public Wall() {
		super('#');
	}

	@Override
	public ActionList allowableActions(Actor actor, Location location, String direction) {
		ActionList actions = new ActionList();
		if(location.containsAnActor() == false && !actor.hasCapability(Status.INVINCIBLE)) {
			actions.add(new Jump(this, location, direction));
		}
		else{
			location.setGround(new Dirt());
			location.addItem(new Coin(5));
		}

		return actions;
	}
	//attempt2ofpush

	
	@Override
	public boolean canActorEnter(Actor actor) {
		if (actor.hasCapability(Status.FLYING)) {
			return true;
		}
		return false;
	}
	
	@Override
	public boolean blocksThrownObjects() {
		return true;
	}


}
