package game.actors;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actions.DoNothingAction;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.displays.Display;
import edu.monash.fit2099.engine.positions.GameMap;
import game.DialogueNames;
import game.actions.*;

public class SusToad extends Actor implements DialogueNames {

    /**
     * This is the Class that represents another merchant that provides services to the Player.
     * The core difference between SusToad and Toad is the payment received, which for SusToad - it's the
     * Player's health unlike Toad where it's Coin.
     */
    public SusToad() {
        super("Suspicious Toad", 'Ø', 666);
    }

    @Override
    public ActionList allowableActions(Actor otherActor, String direction, GameMap map) {
        ActionList actions = new ActionList();
        if(this.isConscious()) {
            personSpeaking();
            actions.add(new susToadSpeakAction(this));
            actions.add(new susToadShopSuperMushroom(this));
            actions.add(new susToadUpgradeWrench(this));
            actions.add(new susToadShopPowerStar(this));
            actions.add(new susToadPokeEyes(this));
        }

        return actions;
    }

    @Override
    public Action playTurn(ActionList actions, Action lastAction, GameMap map, Display display) {
        return new DoNothingAction();
    }

    @Override
    public void personSpeaking() {
        System.out.println("Quite an uncomfortable presence lays here.");
    }
}
