package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;
import game.items.Wrench;

public class susToadSpeakAction extends Action {

    protected Actor target;
    boolean haveWrench = false;
    boolean isPowerStarred = false;

    /**
     *
     * @param target This is the Actor who's speaking to the Player
     * This class is to provide information revolving around the Player and Suspicious Toad himself. This allows
     * the Player to understand what they're missing at that point of the game they're in (in the most
     * degrading way). This also reveals some connections to the Original World's Toad !
     */

    public susToadSpeakAction(Actor target) {
        this.target = target;
    }


    @Override
    public String execute(Actor actor, GameMap map) {
        double rand = Math.random();

        for (Item wrench : actor.getInventory()) {
            if (wrench instanceof Wrench) {
                haveWrench = true;
            }
        }

        if (actor.hasCapability(Status.INVINCIBLE) && actor.hasCapability(Status.DESTROY_GROUND)) {
            isPowerStarred = true;
        }

        if (!actor.hasCapability(Status.INVINCIBLE) && !actor.hasCapability(Status.DESTROY_GROUND)) {
            isPowerStarred = false;
        }

        if (haveWrench == false && isPowerStarred == false) {
            if (rand <= 0.25) {
                return "You're the weakest chump I've met";
            } else if (rand <= 0.5) {
                return "A plumber with no princess....let alone a wrench";
            } else if (rand <= 0.75) {
                return "You're no competition for Bowser, if you can't even handle me";
            } else {
                return "No stars, no wrench, just all guts, huh ?";
            }
        } else if (haveWrench == true && isPowerStarred == false) {
            if (rand <= 0.3333) {
                return "At least you've got a wrench, looked like something my brother owned";
            } else if (rand <= 0.6666) {
                return "I used to bash skulls in with the same wrench";
            } else {
                return "Those pipes workin' or what ?";
            }
        } else if (haveWrench == false && isPowerStarred == true) {
            if (rand <= 0.3333) {
                return "A star with no wrench, perfectly describes you, Mario";
            } else if (rand <= 0.6666) {
                return "You may be invincible, but will you be the star that everyone wishes upon?";
            } else {
                return "That's quite an ugly star you got there";
            }
        } else {
            if (rand <= 0.5) {
                return "Princess Peach wouldn't be danglin' around here, mate";
            } else {
                return "Look at you, thinking you're some hot shot...heh, get it?";
            }

        }

    }



    @Override
    public String menuDescription(Actor actor) {
        return actor + " talks with a suspicious looking Toad" ;
    }
}
