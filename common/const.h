#ifndef CONST_H
#define CONST_H

#define SUCCESS_ 0
#define ERROR_ 1

#define NULL_ARG ""

enum class Direction { LEFT = 0, RIGHT = 1 };

enum class IsMoving { NO = 0, YES = 1 };

enum class JumpDir { FRONT = 0, BACK = 1 };

enum class ADSAngleDir { UP = 0, DOWN = 1 };

enum class DelayAmount { ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5 };

enum class WeaponsAndTools {
    BAZOOKA = 1,
    MORTAR,
    GREEN_GRENADE,
    RED_GRANADE,
    BANANA,
    HOLY_GRENADE,
    DYNAMITE,
    BASEBALL_BAT,
    AIR_STRIKE,
    TELEPORT
};

enum class Actions {
    NULL_,  // Null action

    // Lobby actions
    CREATE,
    JOIN,
    SHOW_GAMES,
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
    CHANGE_WEAPON_OR_TOOL

};

enum class Actors {
    WORM = 0x0,
    GRADIENT = 0x1,
    BRIDGE = 0x2,
    LONG_BRIDGE = 0x3,
    BACKGROUND = 0x4,
    WATER = 0x5
};

enum class StatesTag {
    GAME_FULL,
    GAME_STARTED,
    GAMES_COUNT_L,
    INFO_GAME_L,
    PLAYER_COUNT_L,
    PLAYER_L,
    BATTLEFIELD_G,
    PLAYER_G,
    PROYECTILE_G,
    PLAYER_COUNT_G
};

#endif
