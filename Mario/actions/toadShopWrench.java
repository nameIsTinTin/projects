package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.items.Coin;
import game.items.Wrench;

public class toadShopWrench extends Action {
    protected Actor target;
    protected Integer amount;

    public toadShopWrench(Actor actor){
        this.target = actor;
    }

    @Override
    public String execute(Actor actor, GameMap map) {

        for (Item wrench : actor.getInventory())
        {
            if (wrench instanceof Wrench){
                return ("You already have one!");
            }
        }

        amount = 0;
        for (Item coin : actor.getInventory()) {
            if (coin instanceof Coin) {
                amount = amount + ((Coin) coin).getValue();
            }
        }

        if(amount >= 200) {
            Wrench wrench = new Wrench(50);
            wrench.togglePortability();
            actor.addItemToInventory(wrench);

            for (Item coin : actor.getInventory()) {
                if (coin instanceof Coin) {

                    actor.removeItemFromInventory(coin);
                }
            }
            if(amount - 200 == 0){
                return("My brother who's missing now once loved these Wrenches");}

            else {
                Coin coin = new Coin(amount - 200);
                coin.togglePortability();
                actor.addItemToInventory(coin);
                return ("I'm selling you this knowing you're going to bash skulls in" + "\n" +
                        "Your remaining change of $" + (amount - 200) + " has been added to your inventory");
            }
        }

        else {
            return ("You don't have enough coins!" + "\n" +
                    "Player's inventory:" + actor.getInventory().toString()) + "\n" +
                    "Total amount:" + amount;
        }

    }

    @Override
    public String menuDescription(Actor actor) {
        return(actor + " buys Wrench ($200)");
    }
}
