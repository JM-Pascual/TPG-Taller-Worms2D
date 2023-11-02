#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

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
    PlayerAction() = default;

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
    explicit StartMoving(ServerSide::Protocol&);

    // Delega al servidor el movimiento del gusano
    void execute(Game& game) override;

    ~StartMoving() override = default;
};

// ----------------------- STOP MOVING ----------------------

class StopMoving: public PlayerAction {
public:
    // LLama al constructor de PlayerAction, y recibe a traves del protocolo la direccion a moverse
    StopMoving();

    // Delega al servidor el movimiento del gusano
    void execute(Game& game) override;

    ~StopMoving() override = default;
};

// ----------------------- JUMP ----------------------

class Jump: public PlayerAction {
private:
    JumpDir direction;

public:
    explicit Jump(ServerSide::Protocol& protocol);

    void execute(Game& game) override;

    ~Jump() override = default;
};

// ---------------------- ADSAngle -----------------------

class ADSAngle: public PlayerAction {
private:
    ADSAngleDir direction;

public:
    explicit ADSAngle(ServerSide::Protocol& protocol);

    void execute(Game& game) override;

    ~ADSAngle() override = default;
};

// -------------------- STOP ADS --------------------

class StopADSAngle: public PlayerAction {
public:
    StopADSAngle();

    void execute(Game& game) override;

    ~StopADSAngle() override = default;
};

// ----------------------- ADS DIR ---------------------

class ADSDir: public PlayerAction {
private:
    Direction direction;

public:
    explicit ADSDir(ServerSide::Protocol& protocol);

    void execute(Game& game) override;

    ~ADSDir() = default;
};

// ------------------------- FIRE POWER -----------------

class FirePower: public PlayerAction {
public:
    FirePower();

    void execute(Game& game) override;

    ~FirePower() = default;
};

// ----------------------- SHOOT --------------------

class Shoot: public PlayerAction {
public:
    Shoot();

    void execute(Game& game) override;

    ~Shoot() = default;
};

// -------------------- DELAY ------------------

class Delay: public PlayerAction {
private:
    DelayAmount amount;

public:
    explicit Delay(ServerSide::Protocol& protocol);

    void execute(Game& game) override;

    ~Delay() = default;
};

// ------------------- CHANGE GADGET ---------------------------

class ChangeGadget: public PlayerAction {
private:
    WeaponsAndTools gadget;

public:
    explicit ChangeGadget(ServerSide::Protocol& protocol);

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
    Queue<std::shared_ptr<GameState>>& state_queue;

public:
    explicit Join(GameBrowser& gb, uint8_t& id_to_join,
                  Queue<std::shared_ptr<GameState>>& state_queue,
                  std::atomic<bool>& connected_to_room);

    void execute() override;

    ~Join() override = default;
};

// ----------------------- CREATE ----------------------

class Create: public Join {
public:
    explicit Create(GameBrowser& gb, uint8_t& id_to_create,
                    Queue<std::shared_ptr<GameState>>& state_queue,
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
