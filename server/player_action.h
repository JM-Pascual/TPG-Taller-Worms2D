#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

#include <stdint.h>

#include "../common/GameState.h"
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
    const uint8_t id;

    explicit PlayerAction(const uint8_t id): id(id) {}

    // Da la interfaz para ejecutar el comando
    virtual void execute(Game& game) = 0;

    virtual ~PlayerAction() = default;
};


// ----------------------- START MOVING ----------------------

class StartMoving: public PlayerAction {
private:
    Direction direction;

public:
    // LLama al constructor de PlayerAction, y recibe a traves del protocolo la direccion a moverse
    explicit StartMoving(ServerSide::Protocol& protocol, const uint8_t id);

    // Delega al servidor el movimiento del gusano
    void execute(Game& game) override;

    ~StartMoving() override = default;
};

// ----------------------- STOP MOVING ----------------------

class StopMoving: public PlayerAction {
public:
    // LLama al constructor de PlayerAction, y recibe a traves del protocolo la direccion a moverse
    explicit StopMoving(const uint8_t id);

    // Delega al servidor el movimiento del gusano
    void execute(Game& game) override;

    ~StopMoving() override = default;
};

// ----------------------- JUMP ----------------------

class Jump: public PlayerAction {
private:
    JumpDir direction;

public:
    explicit Jump(ServerSide::Protocol& protocol, const uint8_t id);

    void execute(Game& game) override;

    ~Jump() override = default;
};

// ---------------------- ADSAngle -----------------------

class ADSAngle: public PlayerAction {
private:
    ADSAngleDir direction;

public:
    explicit ADSAngle(ServerSide::Protocol& protocol, const uint8_t id);

    void execute(Game& game) override;

    ~ADSAngle() override = default;
};

// -------------------- STOP ADS --------------------

class StopADSAngle: public PlayerAction {
public:
    explicit StopADSAngle(const uint8_t id);

    void execute(Game& game) override;

    ~StopADSAngle() override = default;
};

// ------------------------- FIRE POWER -----------------

class FirePower: public PlayerAction {
public:
    explicit FirePower(const uint8_t id);

    void execute(Game& game) override;

    ~FirePower() = default;
};

// ----------------------- SHOOT --------------------

class Shoot: public PlayerAction {
public:
    explicit Shoot(const uint8_t id);

    void execute(Game& game) override;

    ~Shoot() = default;
};

// -------------------- DELAY ------------------

class Delay: public PlayerAction {
private:
    DelayAmount amount;

public:
    explicit Delay(ServerSide::Protocol& protocol, const uint8_t id);

    void execute(Game& game) override;

    ~Delay() = default;
};

// ------------------- CHANGE GADGET ---------------------------

class ChangeGadget: public PlayerAction {
private:
    WeaponsAndTools gadget;

public:
    explicit ChangeGadget(ServerSide::Protocol& protocol, const uint8_t id);

    void execute(Game& game) override;

    ~ChangeGadget() = default;
};

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
    const uint8_t& id;
    Queue<std::shared_ptr<GameState>>& state_queue;

public:
    explicit Join(GameBrowser& gb, uint8_t& id_to_join, const uint8_t& id,
                  Queue<std::shared_ptr<GameState>>& state_queue,
                  std::atomic<bool>& connected_to_room);

    void execute() override;

    ~Join() override = default;
};

// ----------------------- CREATE ----------------------

class Create: public Join {
public:
    explicit Create(GameBrowser& gb, uint8_t& id_to_create, const uint8_t& id,
                    Queue<std::shared_ptr<GameState>>& state_queue,
                    std::atomic<bool>& connected_to_room);

    ~Create() override = default;
};

// ----------------------- READY ------------------------

class Ready: public LobbyAction {
private:
    GameBrowser& gb;
    const uint8_t id;
    const uint8_t id_game;

public:
    explicit Ready(GameBrowser& gb, const uint8_t id, const uint8_t id_game):
            gb(gb), id(id), id_game(id_game) {}

    void execute() override;

    ~Ready() = default;
};

// ----------------------- NULL_COMMAND ----------------------

class NullCommand: public PlayerAction, public LobbyAction {
public:
    NullCommand(): PlayerAction(0) {}

    // Comportamiento nulo
    void execute(Game& game) override;

    // Comportamiento nulo
    void execute() override;

    // No hay que liberar nada que no este en stack, destructor default es suficiente.
    ~NullCommand() override = default;
};


#endif
