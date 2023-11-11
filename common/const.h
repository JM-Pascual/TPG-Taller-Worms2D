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
    BAZOOKA = 0x01,
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
    GRADIENT,
    BRIDGE,
    LONG_BRIDGE,
    BACKGROUND,
    WATER,
    JUMPING_WORM,
    BACKFLIP_WORM,
    BAZOOKA_PROYECTILE,
    BAZOOKA_EXPLOSION
};

enum class GameStateTag { BATTLEFIELD, PLAYER, PROYECTILE, PLAYER_COUNT, PROYECTILE_COUNT };

#endif
