#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include "../common/const.h"
#include "../common/queue.h"

class GameBrowser;
class Game;
class Dto;

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
    virtual void execute(Game& game) = 0;

    virtual ~Command() = default;
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
    void execute(Game& game) override;

    ~Move() override = default;
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

// ------------------------ LOBBY COMMANDS -----------------------

class LobbyCommand {
public:
    /*
        Constructor default
    */
    LobbyCommand() = default;
    /*
        Ejecuta el comando
    */
    virtual void execute() = 0;

    virtual ~LobbyCommand() = default;
};

// ----------------------- JOIN ----------------------

class Join: public LobbyCommand {
private:
    GameBrowser& gb;
    uint8_t& game_id;
    std::atomic<bool>& joined_game;
    Queue<std::unique_ptr<Dto>>& game_state;
    
public:
    explicit Join(GameBrowser& gb, uint8_t& id_to_join, Queue<std::unique_ptr<Dto>>& game_state, std::atomic<bool>& connected_to_room);

    void execute() override;

    ~Join() override = default;
};

// ----------------------- CREATE ----------------------

class Create: public Join {
public:
    explicit Create(GameBrowser& gb, uint8_t& id_to_create, Queue<std::unique_ptr<Dto>>& game_state, std::atomic<bool>& connected_to_room);

    ~Create() override = default;
};

// ----------------------- NULL_COMMAND ----------------------

class NullCommand: public Command, public LobbyCommand {
public:
    /*
        Llama al constructor de command
    */
    NullCommand() = default;
    /*
        Null pattern, no hace nada
    */
    void execute(Game& game) override;
    /*
        Null pattern, no hace nada
    */
    void execute() override;
    /*
        No hay que liberar nada que no este en stack, destructor default es suficiente.
    */
    ~NullCommand() override = default;
};


#endif
