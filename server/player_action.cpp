#include "player_action.h"

#include "game_browser.h"
#include "sprotocol.h"

// ----------------------- COMMAND ----------------------

// ----------------------- NULL_COMMAND ----------------------

void NullCommand::execute(Game& game) {}

void NullCommand::execute() {}

// ----------------------- START MOVING ----------------------

StartMoving::StartMoving(ServerSide::Protocol& protocol, const uint8_t id): PlayerAction(id) {
    protocol.recvDirection(this->direction);
}

void StartMoving::execute(Game& game) { game.player_start_moving(direction, id); }

// ----------------------- STOP MOVING ----------------------

StopMoving::StopMoving(const uint8_t id): PlayerAction(id) {}

void StopMoving::execute(Game& game) { game.player_stop_moving(id); }


// ----------------------- JUMP ----------------------

Jump::Jump(ServerSide::Protocol& protocol, const uint8_t id): PlayerAction(id) {
    protocol.recvJumpDir(this->direction);
}

void Jump::execute(Game& game) {}

// ---------------------------- ADSAngle ------------------

ADSAngle::ADSAngle(ServerSide::Protocol& protocol, const uint8_t id): PlayerAction(id) {
    protocol.recvADSAngleDir(this->direction);
}

void ADSAngle::execute(Game& game) {}

// -------------------------- STOP ADS ---------------

StopADSAngle::StopADSAngle(const uint8_t id): PlayerAction(id) {}

void StopADSAngle::execute(Game& game) {}

// ---------------------------- FIRE POWER ------------------

FirePower::FirePower(const uint8_t id): PlayerAction(id) {}

void FirePower::execute(Game& game) {}

// ---------------------------- SHOOT ------------------

Shoot::Shoot(const uint8_t id): PlayerAction(id) {}

void Shoot::execute(Game& game) {}

// ---------------------------- DELAY ------------------

Delay::Delay(ServerSide::Protocol& protocol, const uint8_t id): PlayerAction(id) {
    protocol.recvDelay(this->amount);
}

void Delay::execute(Game& game) {}

// ---------------------------- CHANGE GADGET ------------------

ChangeGadget::ChangeGadget(ServerSide::Protocol& protocol, const uint8_t id): PlayerAction(id) {
    protocol.recvGadget(this->gadget);
}

void ChangeGadget::execute(Game& game) {}

// ----------------------- JOIN ----------------------

Join::Join(GameBrowser& gb, uint8_t& id_to_join, const uint8_t& id,
           Queue<std::shared_ptr<GameState>>& state_queue, std::atomic<bool>& connected_to_room):
        gb(gb),
        game_id(id_to_join),
        joined_game(connected_to_room),
        id(id),
        state_queue(state_queue) {}

void Join::execute() { gb.join_game(game_id, id, state_queue, joined_game); }

// ----------------------- CREATE ----------------------

Create::Create(GameBrowser& gb, uint8_t& id_to_create, const uint8_t& id,
               Queue<std::shared_ptr<GameState>>& state_queue,
               std::atomic<bool>& connected_to_room):
        Join(gb, id_to_create, id, state_queue, connected_to_room) {
    gb.create_game(id_to_create);
}

// ----------------------- READY --------------------

void Ready::execute() { gb.set_player_ready(id, id_game); }
