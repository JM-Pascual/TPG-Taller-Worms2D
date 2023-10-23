#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>

#include "../common/const.h"

namespace ServerSide {
class Protocol;
}

class Command {
protected:
    uint8_t client_id;

public:
    /*
        Asigna la id del cliente
    */
    explicit Command(uint8_t);
    /*
        Ejecuta el comando
    */
    virtual void execute(uint8_t&) = 0;
};

class Move: public Command {
private:
    MoveDir direction;

public:
    /*
        LLama al constructor de Command, y recibe a traves del protocolo la direccion a moverse
    */
    explicit Move(uint8_t, ServerSide::Protocol&);
    /*
        Delega al servidor el movimiento del gusano
    */
    void execute(uint8_t&) override;
};

// class Jump: public Command {
// private:
//     JumpDir direction;

// public:
//     explicit Jump(uint8_t);
// };

// class Damage: public Command {
// private:
//     int8_t dmg;

// public:
//     explicit Damage(uint8_t);
// };


#endif
