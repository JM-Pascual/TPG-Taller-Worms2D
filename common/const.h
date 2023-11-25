#ifndef CONST_H
#define CONST_H

#define SUCCESS_ 0
#define ERROR_ 1

#define NOT_JOINABLE 0
#define NOT_POPPED_COUNT 254
#define CONNECTION_ERROR 255

#define NULL_ARG ""

#define MAX_DESCR_CHARS 64

#define NOT_YOUR_TURN 0
#define IS_YOUR_TURN 1

enum class SWIndex { INTRO, MENU, GAME_SEARCH, HELP, LOBBY };

enum class _CrateType_ { FIRST_AID, AMMO_BOX, TRAP };

enum class Direction { LEFT = 0, RIGHT = 1 };

enum class IsMoving { NO = 0, YES = 1 };

enum class JumpDir { FRONT = 0, BACK = 1 };

enum class ADSAngleDir { UP = 0, DOWN = 1 };

enum class DelayAmount { ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5 };

enum class WeaponsAndTools {
    BAZOOKA = 0x01,
    MORTAR,
    GREEN_GRENADE,
    RED_GRENADE,
    BANANA,
    HOLY_GRENADE,
    DYNAMITE,
    BASEBALL_BAT,
    AIR_STRIKE,
    TELEPORT,
    MORTAR_FRAGMENT
};

enum class Actions {
    NULL_,  // Null action

    // Lobby actions
    CREATE,
    JOIN,
    SHOW_GAMES,
    EXIT_GAME,
    READY,

    // Game actions

    // Movement
    START_MOVING,
    STOP_MOVING,
    JUMP,

    // Fight
    ADS_ANGLE,
    STOP_ADS_ANGLE,
    FIRE_POWER,
    SHOOT,  // stop fpower + shoot
    DELAY,
    CHANGE_WEAPON_OR_TOOL,
    USE_CLICKABLE,

    // Cheats
    WW3,
    RANDOM_KILL,
    INFINITE_AMMO,
    MADNESS,
    IMMORTAL_WORM,
    MULTIPLE_JUMP,
    INFINITE_TURN,
    EVERYONE_1HP

};

enum class Projectiles {
    BAZOOKA_PROYECTILE,
    BANANA_PROYECTILE,
    GREEN_GRENADE_PROYECTILE,
    DYNAMITE_PROYECTILE,
    HOLY_GRENADE_PROYECTILE,
    MORTAR_PROYECTILE,
    MORTAR_FRAGMENT,
    RED_GRENADE_PROYECTILE
};

enum class Tombstones {
    TOMBSTONE_1 = 0x1,
    TOMBSTONE_2,
    TOMBSTONE_3,
    TOMBSTONE_4,
    TOMBSTONE_5,
    TOMBSTONE_6
};

enum class Effects { NORMAL_EXPLOSION, FRAGMENT_EXPLOSION };

enum class Actors {
    WORM = 0x0,
    GRADIENT,
    BRIDGE,
    LONG_BRIDGE,
    BACKGROUND,
    CRATE,
    CRATE_FALLING,
    WATER,
    JUMPING_WORM,
    BACKFLIP_WORM,
    DYING_WORM,
    CROSSHAIR,
    POWER_CHARGE_BAR,
    STATE_SIGN
};

enum class WeaponsDraw {
    WORM_DRAW_BAZOOKA,
    WORM_DRAW_BANANA,
    WORM_DRAW_HOLY_GRENADE,
    WORM_DRAW_AIR_STRIKE,
    WORM_DRAW_BASEBALL_BAT,
    WORM_DRAW_DYNAMITE,
    WORM_DRAW_GREEN_GRENADE,
    WORM_DRAW_MORTAR,
    WORM_DRAW_RED_GRENADE,
    WORM_DRAW_TELEPORT
};

enum class WeaponAiming {
    WORM_AIM_BAZOOKA,
    WORM_AIM_BANANA,
    WORM_AIM_HOLY_GRENADE,
    WORM_AIM_AIR_STRIKE,
    WORM_AIM_BASEBALL_BAT,
    WORM_AIM_DYNAMITE,
    WORM_AIM_GREEN_GRENADE,
    WORM_AIM_MORTAR,
    WORM_AIM_RED_GRENADE,
    WORM_AIM_TELEPORT
};

enum class StatesTag {
    GAME_NOT_JOINABLE,
    CONNECTION_ERROR_STATE,
    GAMES_COUNT_L,
    INFO_GAME_L,
    PLAYER_COUNT_L,
    PLAYER_L,
    BATTLEFIELD_G,
    PLAYER_G,
    PROJECTILE_G,
    PLAYER_TURN,
    WORM_G,
    CRATE
};

#endif
