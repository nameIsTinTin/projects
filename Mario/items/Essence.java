package game.items;

import edu.monash.fit2099.engine.items.Item;

public class Essence extends Item {
    /**
     * This Class represents the Item dropped by Bowsette which cannot be interacted with at all. However,
     * the Player can submit this Item to Toad that will grant the Player additional powers.
     */
    public Essence(){
        super("Essence of Armaggedon", '★', true);
    }
}
