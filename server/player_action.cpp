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
// ToDo por ahora start moving y stop moving son iguales y no discriminan por direccion
void StartMoving::execute(Game& game) { game.player_start_moving(); }

// ----------------------- STOP MOVING ----------------------

StopMoving::StopMoving(): PlayerAction() {}

void StopMoving::execute(Game& game) { game.player_stop_moving(); }


// ----------------------- JUMP ----------------------

// Jump::Jump(): PlayerAction(id) {}


// ----------------------- DAMAGE ----------------------

// Damage::Damage(): PlayerAction(id) {}

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
