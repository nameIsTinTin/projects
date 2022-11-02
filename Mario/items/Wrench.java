package game.items;

import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.weapons.WeaponItem;
import java.util.Random;

/**
 * A WeaponItem representing a Wrench.
 */
public class Wrench extends WeaponItem {

    /**
     * Constructor.
     */
    int current_damage;



    public Wrench(int damage) {


        super("Wrench", 'w', damage, "whacks", 80);
        this.current_damage = damage;
    }

    public int upgradeWrench(){
        Random rand = new Random();
        int upperbound = 41;
        int random_upgrade = rand.nextInt(upperbound);
        return(random_upgrade);
    }

    public int getCurrent_damage(){
        return current_damage;
    }

}
