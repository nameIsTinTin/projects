package game;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;

public class ResetAction extends Action {

    @Override
    public String execute(Actor actor, GameMap map) {
        actor.removeCapability(Status.RESETTABLE);
        ResetManager.getInstance().run();
        return "The game has resetted.";
    }

    @Override
    public String menuDescription(Actor actor) {
        return "Reset the game.";
    }

    @Override
    public String hotkey() {
        return "r";
    }
}
