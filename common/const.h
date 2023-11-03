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
    NULL_ = 0x0,  // Null action

    // Lobby actions
    CREATE = 0x1,
    JOIN = 0x2,
    SHOW_GAMES = 0x3,

    // Game actions

    // Movement
    START_MOVING = 0x4,
    STOP_MOVING = 0x5,
    JUMP = 0x6,

    // Fight
    ADS_ANGLE = 0x7,
    STOP_ADS_ANGLE = 0x8,
    FIRE_POWER = 0x9,
    SHOOT = 0xa,  // stop fpower + shoot
    DELAY = 0xb,
    CHANGE_WEAPON_OR_TOOL = 0xc

};

enum class Actors {
    WORM = 0x0,
    GRADIENT = 0x1,
    BRIDGE = 0x2,
    LONG_BRIDGE = 0x3,
    BACKGROUND = 0x4,
    WATER = 0x5
};

#endif
