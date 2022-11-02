package game.magicalfountain;
/**
 * Class for Water representing the type of water in fountain
 */
public class Water {

    private String waterName;

    /**
     * Constructor.
     *
     * @param waterName the water name
     * */
    public Water(String waterName){
        this.waterName=waterName;
    }

    /**
     * Getter to retrieve water name
     *
     * Return water name
     * */
    public String getWaterName(){
        return this.waterName;
    }

    /**
     * toString method
     * */
    public String toString(){
        return waterName;
    }
}
