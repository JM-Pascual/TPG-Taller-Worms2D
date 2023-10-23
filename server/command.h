#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include <stdint.h>

#include "../common/const.h"

#include "lobby.h"

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
    // Este int no tiene que ir, supongo que sera un metodo sin args. Esta de momento
    // por la simulacion experimental de moverse
    virtual ~Command() = default;
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

    ~Move() override = default;
};

class Create: public Command {
private:
    Lobby& lobby;
    uint8_t game_id;
    std::unique_ptr<LobbyClient>& client;

public:
    /*

    */
    explicit Create(uint8_t, ServerSide::Protocol&, Lobby& lobby,
                    std::unique_ptr<LobbyClient>& client);
    /*

    */
    void execute(uint8_t&) override;

    ~Create() override = default;
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
