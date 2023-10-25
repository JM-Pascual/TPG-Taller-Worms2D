#ifndef CONST_H
#define CONST_H

#define SUCCESS_ 0
#define ERROR_ 1

#define NULL_ARG ""

enum class MoveDir { LEFT = 0, RIGHT = 1 };

enum class JumpDir { FRONT = 0, BACK = 1 };

enum class Commands { CREATE = 0x1, JOIN = 0x2, MOVE = 0x3, JUMP = 0x4 };

#endif
