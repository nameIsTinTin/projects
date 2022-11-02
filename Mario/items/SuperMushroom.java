
package game.items;

import edu.monash.fit2099.engine.items.Item;
import game.actions.ConsumeSuperMushroomAction;
//supermushroom
/**
 * Class representing SuperMushroom
 */
public class SuperMushroom extends Item{
    /***
     * Constructor.
     *
     */
    public SuperMushroom(){
        super("Super Mushroom", '^',true);
        this.addAction(new ConsumeSuperMushroomAction(this));
    }

}
