#include "player_action.h"

#include "game_browser.h"
#include "sprotocol.h"

// ----------------------- COMMAND ----------------------

// ----------------------- NULL_COMMAND ----------------------

void NullCommand::execute(Game& game) {}

void NullCommand::execute() {}

// ----------------------- START MOVING ----------------------

StartMoving::StartMoving(ServerSide::Protocol& protocol): PlayerAction() {
    protocol.recvDirection(this->direction);
}

void StartMoving::execute(Game& game) { game.player_start_moving(direction); }

// ----------------------- STOP MOVING ----------------------

StopMoving::StopMoving(): PlayerAction() {}

void StopMoving::execute(Game& game) { game.player_stop_moving(); }


// ----------------------- JUMP ----------------------

Jump::Jump(ServerSide::Protocol& protocol) { protocol.recvJumpDir(this->direction); }

void Jump::execute(Game& game) {}

// ---------------------------- ADSAngle ------------------

ADSAngle::ADSAngle(ServerSide::Protocol& protocol) { protocol.recvADSAngleDir(this->direction); }

void ADSAngle::execute(Game& game) {}

// -------------------------- STOP ADS ---------------

StopADSAngle::StopADSAngle(): PlayerAction() {}

void StopADSAngle::execute(Game& game) {}

// ---------------------------- FIRE POWER ------------------

FirePower::FirePower(): PlayerAction() {}

void FirePower::execute(Game& game) {}

// ---------------------------- SHOOT ------------------

Shoot::Shoot(): PlayerAction() {}

void Shoot::execute(Game& game) {}

// ---------------------------- DELAY ------------------

Delay::Delay(ServerSide::Protocol& protocol) { protocol.recvDelay(this->amount); }

void Delay::execute(Game& game) {}

// ---------------------------- CHANGE GADGET ------------------

ChangeGadget::ChangeGadget(ServerSide::Protocol& protocol) { protocol.recvGadget(this->gadget); }

void ChangeGadget::execute(Game& game) {}

// ----------------------- JOIN ----------------------

Join::Join(GameBrowser& gb, uint8_t& id_to_join, Queue<std::shared_ptr<GameState>>& state_queue,
           std::atomic<bool>& connected_to_room):
        gb(gb), game_id(id_to_join), joined_game(connected_to_room), state_queue(state_queue) {}

void Join::execute() { gb.join_game(game_id, state_queue, joined_game); }

// ----------------------- CREATE ----------------------

Create::Create(GameBrowser& gb, uint8_t& id_to_create,
               Queue<std::shared_ptr<GameState>>& game_state, std::atomic<bool>& connected_to_room):
        Join(gb, id_to_create, game_state, connected_to_room) {
    gb.create_game(id_to_create);
}
