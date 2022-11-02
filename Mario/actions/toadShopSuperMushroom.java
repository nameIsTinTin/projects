package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.items.Coin;
import game.items.SuperMushroom;

public class toadShopSuperMushroom extends Action {

    protected Actor target;
    protected Integer amount;

    public toadShopSuperMushroom(Actor actor){
        this.target = actor;
    }

    @Override
    public String execute(Actor actor, GameMap map) {

        amount = 0;
        for (Item coin : actor.getInventory()) {
            if (coin instanceof Coin) {
                amount = amount + ((Coin) coin).getValue();
            }
        }

        if(amount >= 400) {
            SuperMushroom superMushroom = new SuperMushroom();
            superMushroom.togglePortability();
            actor.addItemToInventory(superMushroom);

            for (Item coin : actor.getInventory()) {
                if (coin instanceof Coin) {
                    actor.removeItemFromInventory(coin);
                }
            }
            if(amount - 400 == 0) {
                return ("All of your money for shrooms? Disappointing...");
            }
            else{
                Coin coin = new Coin(amount - 400);
                coin.togglePortability();
                actor.addItemToInventory(coin);
            return("A toad selling shrooms...is this legal?" + "\n" +
                    "Your remaining change of $" + (amount-400) + " has been added to your inventory");
        }}

        else {
            return ("You don't have enough coins!" + "\n" +
                    "Player's inventory:" + actor.getInventory().toString()) + "\n" +
                    "Total amount:" + amount;
        }

    }


    @Override
    public String menuDescription(Actor actor) {
        return(actor + " buys Super Mushroom ($400)");
    }
}
