#ifndef COMMAND_H
#define COMMAND_H

#include <memory>
#include <string>
#include <vector>

#include <stdint.h>

#include "../common/States.h"
#include "../common/const.h"
#include "../common/queue.h"

class WormHandler;
class TurnHandler;
class GameBrowser;

namespace ServerSide {
class Protocol;
}

// ----------------------- PLAYER ACTIONS INTERFACE ----------------------

class PlayerAction {
public:
    const uint8_t id;

    explicit PlayerAction(const uint8_t& id): id(id) {}

    // Da la interfaz para ejecutar el comando
    virtual void execute(WormHandler& worm_handler, const uint8_t& turn_id,
                         const uint8_t& worm_index, TurnHandler& turn_handler) = 0;

    virtual ~PlayerAction() = default;
};


// ----------------------- START MOVING ----------------------

class StartMoving: public PlayerAction {
private:
    Direction direction;

public:
    // LLama al constructor de PlayerAction, y recibe a traves del protocolo la direccion a moverse
    explicit StartMoving(ServerSide::Protocol& protocol, const uint8_t& id);

    // Delega al servidor el movimiento del gusano
    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~StartMoving() override = default;
};

// ----------------------- STOP MOVING ----------------------

class StopMoving: public PlayerAction {
public:
    // LLama al constructor de PlayerAction, y recibe a traves del protocolo la direccion a moverse
    explicit StopMoving(const uint8_t& id);

    // Delega al servidor el movimiento del gusano
    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~StopMoving() override = default;
};

// ----------------------- JUMP ----------------------

class Jump: public PlayerAction {
private:
    JumpDir direction;

public:
    explicit Jump(ServerSide::Protocol& protocol, const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~Jump() override = default;
};

// ---------------------- ADSAngle -----------------------

class ADSAngle: public PlayerAction {
private:
    ADSAngleDir direction;

public:
    explicit ADSAngle(ServerSide::Protocol& protocol, const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~ADSAngle() override = default;
};

// -------------------- STOP ADS --------------------

class StopADSAngle: public PlayerAction {
public:
    explicit StopADSAngle(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~StopADSAngle() override = default;
};

// ------------------------- FIRE POWER -----------------

class FirePower: public PlayerAction {
public:
    explicit FirePower(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~FirePower() = default;
};

// ----------------------- SHOOT --------------------

class Shoot: public PlayerAction {
public:
    explicit Shoot(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~Shoot() = default;
};

// -------------------- DELAY ------------------

class Delay: public PlayerAction {
private:
    DelayAmount amount;

public:
    explicit Delay(ServerSide::Protocol& protocol, const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~Delay() = default;
};

// ---------------------- USE CLICKABLE ---------------------------

class UseClickable: public PlayerAction {
private:
    b2Vec2 position;

public:
    explicit UseClickable(ServerSide::Protocol& protocol, const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~UseClickable() = default;
};

// ------------------- CHANGE GADGET ---------------------------

class ChangeGadget: public PlayerAction {
private:
    WeaponsAndTools gadget;

public:
    explicit ChangeGadget(ServerSide::Protocol& protocol, const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~ChangeGadget() = default;
};

class WW3Cheat: public PlayerAction {
public:
    explicit WW3Cheat(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~WW3Cheat() = default;
};

class NoWindCheat: public PlayerAction {
public:
    explicit NoWindCheat(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~NoWindCheat() = default;
};

class InfiniteAmmoCheat: public PlayerAction {
public:
    explicit InfiniteAmmoCheat(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~InfiniteAmmoCheat() = default;
};

class MadnessCheat: public PlayerAction {
public:
    explicit MadnessCheat(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~MadnessCheat() = default;
};

class ImmortalWorm: public PlayerAction {
public:
    explicit ImmortalWorm(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~ImmortalWorm() = default;
};

class MultipleJumpCheat: public PlayerAction {
public:
    explicit MultipleJumpCheat(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~MultipleJumpCheat() = default;
};

class InfiniteTurnCheat: public PlayerAction {
public:
    explicit InfiniteTurnCheat(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~InfiniteTurnCheat() = default;
};

class Everyone1HPCheat: public PlayerAction {
public:
    explicit Everyone1HPCheat(const uint8_t& id);

    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    ~Everyone1HPCheat() = default;
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
    const uint8_t& id;
    Queue<std::shared_ptr<States>>& state_queue;

public:
    explicit Join(GameBrowser& gb, uint8_t& id_to_join, const uint8_t& id,
                  Queue<std::shared_ptr<States>>& state_queue);

    void execute() override;

    ~Join() override = default;
};

// ----------------------- CREATE ----------------------

class Create: public Join {
private:
    std::string desc;
    std::string map;

public:
    explicit Create(GameBrowser& gb, uint8_t& id_to_create, const uint8_t& id,
                    Queue<std::shared_ptr<States>>& state_queue, ServerSide::Protocol& protocol);

    ~Create() override = default;
};

// ----------------------- READY ------------------------

class Ready: public LobbyAction {
private:
    GameBrowser& gb;
    const uint8_t id;
    const uint8_t id_game;

public:
    explicit Ready(GameBrowser& gb, const uint8_t& id, const uint8_t& id_game):
            gb(gb), id(id), id_game(id_game) {}

    void execute() override;

    ~Ready() = default;
};

class ShowGames: public LobbyAction {
private:
    std::vector<std::shared_ptr<GameInfoL>> info;
    GameBrowser& gb;
    Queue<std::shared_ptr<States>>& state_queue;

public:
    ShowGames(GameBrowser& gb, Queue<std::shared_ptr<States>>& stateQ):
            gb(gb), state_queue(stateQ) {}

    void execute() override;

    ~ShowGames() = default;
};

class ExitGame: public LobbyAction {
private:
    GameBrowser& gb;
    const uint8_t& player_id;
    const uint8_t& game_id;

public:
    ExitGame(GameBrowser& gb, const uint8_t& player_id, const uint8_t& game_id):
            gb(gb), player_id(player_id), game_id(game_id) {}

    void execute() override;

    ~ExitGame() = default;
};

// ----------------------- NULL_COMMAND ----------------------

class NullCommand: public PlayerAction, public LobbyAction {
public:
    NullCommand(): PlayerAction(0) {}

    // Comportamiento nulo
    void execute(WormHandler& worm_handler, const uint8_t& turn_id, const uint8_t& worm_index,
                 TurnHandler& turn_handler) override;

    // Comportamiento nulo
    void execute() override;

    // No hay que liberar nada que no este en stack, destructor default es suficiente.
    ~NullCommand() override = default;
};


#endif
