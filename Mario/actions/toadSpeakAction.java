package game.actions;


import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;
import game.items.Wrench;

/**
 * A class that allows the Actor Toad to say different lines
 * depending on the target Actor's situation.
 */
public class toadSpeakAction extends Action {

    /**
     * The Actor that is to be talked to.
     */
    protected Actor target;

    /**
     * A boolean to check whether an actor has the wrench.
     */
    private boolean haveWrench = false;

    /**
     * A boolean to check whether an actor is currently powerstarred.
     */
    private boolean isPowerStarred = false;

    /**
     * Constructor.
     *
     * @param target the Actor to talk to
     */
    public toadSpeakAction(Actor target){
        this.target = target;
    }

    /**
     * Checks whether an actor has a wrench or is powerstarred and returns different
     * strings based on those conditions.
     * @param actor The actor performing the action.
     * @param map The map the actor is on.
     * @return a String
     */
    @Override
    public String execute(Actor actor, GameMap map) {
        double rand = Math.random();


        for (Item wrench : actor.getInventory()){
            if (wrench instanceof Wrench){
                haveWrench = true;
            }
        }

        if (actor.hasCapability(Status.INVINCIBLE) && actor.hasCapability(Status.DESTROY_GROUND)){
            isPowerStarred = true;
        }

        if (!actor.hasCapability(Status.INVINCIBLE) && !actor.hasCapability(Status.DESTROY_GROUND)){
            isPowerStarred = false;
        }


        if (haveWrench == false && isPowerStarred == false) {
            if (rand <= 0.25) {
                return "You might need a wrench to smash Koopa's hard shells.";
            } else if (rand <= 0.5) {
                return "You better get back to finding the Power Stars.";
            } else if (rand <= 0.75) {
                return "The Princess is depending on you! You are our only hope.";
            } else {
                return "Being imprisoned in these walls can drive a fungus crazy :(";
            }
        } else if (haveWrench == true && isPowerStarred == false) {
            if (rand <= 0.3333) {
                return "You better get back to finding the Power Stars.";
            } else if (rand <= 0.6666) {
                return "The Princess is depending on you! You are our only hope.";
            } else {
                return "Being imprisoned in these walls can drive a fungus crazy :(";
            }
        } else if (haveWrench == false && isPowerStarred == true) {
            if (rand <= 0.3333) {
                return "You might need a wrench to smash Koopa's hard shells.";
            } else if (rand <= 0.6666) {
                return "The Princess is depending on you! You are our only hope.";
            } else {
                return "Being imprisoned in these walls can drive a fungus crazy :(";
            }
        } else {
            if (rand <= 0.5) {
                return "The Princess is depending on you! You are our only hope.";
            } else {
                return "Being imprisoned in these walls can drive a fungus crazy :(";
            }

        }
    }

    /**
     * Allows the actor to talk to a target in the menu description.
     * @param actor The actor performing the action.
     * @return a String
     */
    @Override
    public String menuDescription(Actor actor) {
        return actor + " talks with " + target;
    }
}
