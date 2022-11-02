package game;

/**
 * Use this enum class to give `buff` or `debuff`.
 * It is also useful to give a `state` to abilities or actions that can be attached-detached.
 */
///status
public enum Status {
    HOSTILE_TO_ENEMY, // use this status to be considered hostile towards enemy (e.g., to be attacked by enemy)
    TALL, // use this status to tell that current instance has "grown".
    DORMANTABLE, // use this status to show if something can be dormant after it is not conscious.
    FERTILE,
    JUMP_FREELY, //when super mushroom is consumed
    INVINCIBLE, //when power star is consumed
    DESTROY_GROUND, //when power star is consumed
    EVOLVE_TO_UPPER_CASE, //when super mushroom is consumed
    ACTIVE, // use this status to show if an item is in effect while it is in the inventory
    RESETTABLE,
    FLYING, // use this status to show if an actor can travel over higher planes
    FIREATTACK, // use this status when an actor's attack causes the ground below their target to burn

    OBTAIN_BOTTLE, //Creative mode(when a jump on wall is successful, the player can get bottle from toad)
    BOTTLE_IN_ITEM, //when the player obtained the bottle from toad
    DRANK, //track how many times the water is being consumed
    REFILLED, //track how many times the water is refilled in bottle
    CAN_DRINK, //Enemy can drink water from fountain directly
    BASE_ATTACK_DAMAGE_INCREASE,
    SUCCESSFUL_JUMP, //can upgrade bottle charges
    BEING_JUDGED, //Creative mode (when an actor enters through the portal, they cannot enter another with this status)
    LIBERATED, //use when Bowsette is defeated
    GOD, //use when Mario gives Toad the Essence of Armageddon
    RESETTING, //use to indicate if something is about to be resetted.

}
