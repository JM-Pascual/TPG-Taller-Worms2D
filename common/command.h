#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>

#include "const.h"

class Command {
protected:
    uint8_t client_id;

public:
    explicit Command(uint8_t);
};

class Move: public Command {
private:
    MoveDir direction;

public:
    explicit Move(uint8_t, MoveDir);
};

class Jump: public Command {
private:
    JumpDir direction;

public:
    explicit Jump(uint8_t, JumpDir);
};

class Damage: public Command {
private:
    int8_t dmg;

public:
    explicit Damage(uint8_t, int8_t);
};


#endif
