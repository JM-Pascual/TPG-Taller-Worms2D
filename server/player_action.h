#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include "../common/WormGameState.h"
#include "../common/const.h"
#include "../common/queue.h"

#include "Game.h"

class GameBrowser;

namespace ServerSide {
class Protocol;
}

// ----------------------- PLAYER ACTIONS INTERFACE ----------------------

class PlayerAction {
public:
    PlayerAction() = default;

    // Da la interfaz para ejecutar el comando
    virtual void execute(Game& game) = 0;

    virtual ~PlayerAction() = default;
};


// ----------------------- START MOVING ----------------------

class StartMoving: public PlayerAction {
private:
    MoveDir direction;

public:
    // LLama al constructor de PlayerAction, y recibe a traves del protocolo la direccion a moverse
    explicit StartMoving(ServerSide::Protocol&);

    // Delega al servidor el movimiento del gusano
    void execute(Game& game) override;

    ~StartMoving() override = default;
};

// ----------------------- STOP MOVING ----------------------

class StopMoving: public PlayerAction {
public:
    // LLama al constructor de PlayerAction, y recibe a traves del protocolo la direccion a moverse
    explicit StopMoving();

    // Delega al servidor el movimiento del gusano
    void execute(Game& game) override;

    ~StopMoving() override = default;
};

// ----------------------- JUMP ----------------------

// class Jump: public PlayerAction {
// private:
//     JumpDir direction;

// public:
//     explicit Jump(uint8_t);
// };

// ----------------------- DAMAGE ----------------------

// class Damage: public PlayerAction {
// private:
//     int8_t dmg;

// public:
//     explicit Damage(uint8_t);
// };

// ------------------------ LOBBY ACTIONS -----------------------

class LobbyAction {
public:
    /*
        Constructor default
    */
    LobbyAction() = default;
    /*
        Ejecuta el comando
    */
    virtual void execute() = 0;

    virtual ~LobbyAction() = default;
};

// ----------------------- JOIN ----------------------

class Join: public LobbyAction {
private:
    GameBrowser& gb;
    uint8_t& game_id;
    std::atomic<bool>& joined_game;
    Queue<std::shared_ptr<WormGameState>>& state_queue;

public:
    explicit Join(GameBrowser& gb, uint8_t& id_to_join,
                  Queue<std::shared_ptr<WormGameState>>& state_queue,
                  std::atomic<bool>& connected_to_room);

    void execute() override;

    ~Join() override = default;
};

// ----------------------- CREATE ----------------------

class Create: public Join {
public:
    explicit Create(GameBrowser& gb, uint8_t& id_to_create,
                    Queue<std::shared_ptr<WormGameState>>& state_queue,
                    std::atomic<bool>& connected_to_room);

    ~Create() override = default;
};

// ----------------------- NULL_COMMAND ----------------------

class NullCommand: public PlayerAction, public LobbyAction {
public:
    NullCommand() = default;

    // Comportamiento nulo
    void execute(Game& game) override;

    // Comportamiento nulo
    void execute() override;

    // No hay que liberar nada que no este en stack, destructor default es suficiente.
    ~NullCommand() override = default;
};


#endif
