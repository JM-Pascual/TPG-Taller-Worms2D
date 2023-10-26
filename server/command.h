#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include <stdint.h>

#include "../common/const.h"

class Lobby;

namespace ServerSide {
class Protocol;
}

// ----------------------- COMMAND ----------------------

class Command {
public:
    /*
        Constructor default
    */
    Command() = default;
    /*
        Ejecuta el comando
    */
    virtual void execute() = 0;
    // Este int no tiene que ir, supongo que sera un metodo sin args. Esta de momento
    // por la simulacion experimental de moverse
    virtual ~Command() = default;
};

// ----------------------- NULL_COMMAND ----------------------

class NullCommand: public Command {
public:
    /*
        Llama al constructor de command
    */
    NullCommand() = default;
    /*
        Null pattern, no hace nada
    */
    void execute() override;
    /*
        No hay que liberar nada que no este en stack, destructor default es suficiente.
    */
    ~NullCommand() override = default;
};

// ----------------------- MOVE ----------------------

class Move: public Command {
private:
    MoveDir direction;

public:
    /*
        LLama al constructor de Command, y recibe a traves del protocolo la direccion a moverse
    */
    explicit Move(ServerSide::Protocol&);
    /*
        Delega al servidor el movimiento del gusano
    */
    void execute() override;

    ~Move() override = default;
};

// ----------------------- JOIN ----------------------

class Join: public Command {
private:
    Lobby& lobby;
    uint8_t game_id;
    uint8_t client_id;

public:
    explicit Join(Lobby& lobby, uint8_t id, uint8_t game_id);

    void execute() override;

    virtual ~Join() override = default;
};

// ----------------------- CREATE ----------------------

class Create: public Join {
public:
    /*

    */
    explicit Create(uint8_t id, Lobby& lobby);

    ~Create() override = default;
};

// ----------------------- JUMP ----------------------

// class Jump: public Command {
// private:
//     JumpDir direction;

// public:
//     explicit Jump(uint8_t);
// };

// ----------------------- DAMAGE ----------------------

// class Damage: public Command {
// private:
//     int8_t dmg;

// public:
//     explicit Damage(uint8_t);
// };


#endif
