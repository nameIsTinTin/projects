package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.positions.GameMap;
import game.Status;
import game.positions.Portal;

public class susToadPokeEyes extends Action {




    protected Actor target;

    /**
     *
     * @param actor This is the parameter of the actor's eyes been poked
     * This class is to initiate an end-game event - as once this has been executed, the actor will be removed
     * from the map and the Portal Ground underneath the actor will be revealed which the Player can teleport to.
     * In addition, this class also sends the Player flying to the corner of the map.
     */

    public susToadPokeEyes(Actor actor){
        this.target = actor;
    }

    @Override
    public String execute(Actor actor, GameMap map) {

        target.hurt(666);
        map.moveActor(actor, map.at(61, 0) );
        map.removeActor(target);
        return("GAHHHHH MY EYES !!!? BEGONE !");
    }

    @Override
    public String menuDescription(Actor actor) {
        return actor + " pokes Suspicious Toad's eyes";
    }
}
