package game.items;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actions.ActionList;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.items.PickUpItemAction;
import edu.monash.fit2099.engine.positions.Location;
import game.Resettable;
import game.Status;

import java.util.List;

public class Coin extends Item implements Resettable {
    private int value;


    public Coin(int value) {
        super("Coin", '$', true);
        this.value = value;
        this.registerInstance();
    }

    public int getValue() {
        return value;
    }

    public void tick(Location currentLocation) {
        if (this.hasCapability(Status.RESETTING))
            currentLocation.removeItem(this);
    }

    @Override
    public void resetInstance() {
        this.addCapability(Status.RESETTING);
    }
}
