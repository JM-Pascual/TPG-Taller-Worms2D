#ifndef CONST_H
#define CONST_H

#define SUCCESS_ 0
#define ERROR_ 1

#define NOT_JOINABLE 0
#define NOT_POPPED_COUNT 254
#define CONNECTION_ERROR 255

#define NULL_ARG ""

#define MAX_DESCR_CHARS 64
#define MAX_PLAYERS 4

enum class SWIndex { INTRO, MENU, GAME_SEARCH, HELP, LOBBY };

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
    TELEPORT
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
    CROSSHAIR,
    WORM_DRAW_BAZOOKA,
    WORM_HOLDING_BAZOOKA,
    BAZOOKA_PROYECTILE,
    BAZOOKA_EXPLOSION
};

enum class GameEntity {
    WORM,
    BAZOOKA,
    MORTAR,
    GREEN_GRENADE,
    RED_GRENADE,
    HOLY_GRENADE,
    BANANA,
    DYNAMITE,
    BASEBALL_BAT,
    AIR_ATTACK
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
    PROJECTILE_COUNT_G,
    PLAYER_COUNT_G
};

#endif
