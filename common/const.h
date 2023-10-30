#ifndef CONST_H
#define CONST_H

#define SUCCESS_ 0
#define ERROR_ 1

#define NULL_ARG ""

enum class MoveDir { LEFT = 0, RIGHT = 1 };

enum class IsMoving { NO = 0, YES = 1 };

enum class JumpDir { FRONT = 0, BACK = 1 };

enum class Actions {
    NULL_ = 0x0,
    CREATE = 0x1,
    JOIN = 0x2,
    SHOW_GAMES = 0x3,
    START_MOVING = 0x4,
    STOP_MOVING = 0x5,
    JUMP = 0x6
};

#endif
