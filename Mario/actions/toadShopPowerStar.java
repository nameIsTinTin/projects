package game.actions;

import edu.monash.fit2099.engine.actions.Action;
import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.positions.GameMap;
import game.items.Coin;
import game.items.PowerStar;


public class toadShopPowerStar extends Action {

    protected Actor target;
    protected Integer amount;


    public toadShopPowerStar(Actor actor){
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

        if(amount >= 600) {
            PowerStar powerStar = new PowerStar();
            powerStar.togglePortability();
            actor.addItemToInventory(powerStar);

            for (Item coin : actor.getInventory()) {
                if (coin instanceof Coin) {
                    actor.removeItemFromInventory(coin);
                }
            }
            if(amount - 600 == 0){
                return("Your wallet looks pretty dark in comparison to what you've bought, heh");}

            else {
                Coin coin = new Coin(amount - 600);
                coin.togglePortability();
                actor.addItemToInventory(coin);
                return ("A Power Star for a Super Star!" + "\n" +
                        "Your remaining change of $" + (amount - 600) + " has been added to your inventory");
            }
        }

        else {
            return ("You don't have enough coins!" + "\n" +
                    "Player's inventory:" + actor.getInventory().toString()) + "\n" +
                    "Total amount:" + amount;
        }
        /*
        return ("Existence of Coin:" + actor.getInventory().contains(Coin.class) + "\n" +
                "Player's inventory:" + actor.getInventory().toString()) + "\n" +
                "Total amount:" + amount;

         */
    }

    @Override
    public String menuDescription(Actor actor) {
        return(actor + " buys Power Star ($600)");
    }
}
