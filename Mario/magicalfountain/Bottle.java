package game.magicalfountain;

import edu.monash.fit2099.engine.actors.Actor;
import edu.monash.fit2099.engine.items.DropItemAction;
import edu.monash.fit2099.engine.items.Item;
import edu.monash.fit2099.engine.items.PickUpItemAction;

import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Objects;
//bottle class
/**
 * Class representing a bottle object in the game world.
 *
 */
public class Bottle extends Item {
    private ArrayList<Water> bottleContent;
    private String waterNameInBottle;
    private int bottleCapacity;

    /***
     * Constructor.
     */
    public Bottle() {
        super("bottle", 'b', true);
        bottleContent=new ArrayList<>();
        bottleCapacity=10;

    }


    /**
     * Create and return an action to drop this Item.
     * If this Item is not portable, returns null.
     * @return a new DropItemAction if this Item is portable, null otherwise.
     */
    @Override
    public DropItemAction getDropAction(Actor actor) {
        return null;
    }


    /**
     * Add water in the bottle
     * @param waterName a new water object to be added in bottle
     */
    public void addWater(Water waterName){
        bottleContent.add(waterName);


    }

    /**
     * Remove water in the bottle
     * @param index index of water in arraylist that will be removed
     */
    public void removeWater(int index){
        bottleContent.remove(index);
    }


    /**
     * return the index of last water in the bottle
     * @return int that representing the last index of water in the bottle
     */
    public int getLastWaterIndex(){
        return bottleContent.size()-1;
    }

    /**
     * return the last water name in the bottle
     * @return String that representing the last water in the bottle
     */
    public String getLastWaterString(int index){
        String ret= String.valueOf(bottleContent.get(index));
        return ret;
    }
    /**
     * return the arraylist of all the water in bottle
     * @return ArrayList that representing all the water in the bottle
     */
    public ArrayList<Water> getBottleContent() {
        return bottleContent;
    }

    /**
     * Setter to set the bottle capacity
     * @param newBottleCapacity that representing the new bottle capacity
     */
    public void setBottleCapacity(int newBottleCapacity){
        this.bottleCapacity=newBottleCapacity;
    }

    /**
     * Getter to retrieve the capacity of the bottle
     * @return int that representing capacity of the bottle
     */
    public int getBottleCapacity(){
        return getBottleContent().size();
    }

    /**
     * return the max capacity of bottle
     * @return int that representing the current max capacity of the bottle
     */
    public int maxBottleCapacity(){
        return this.bottleCapacity;
    }



}