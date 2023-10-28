#include "command.h"

#include "game_browser.h"
#include "sprotocol.h"

// ----------------------- COMMAND ----------------------

// ----------------------- NULL_COMMAND ----------------------

void NullCommand::execute(Game& game) {}

void NullCommand::execute() {}

// ----------------------- MOVE ----------------------

Move::Move(ServerSide::Protocol& protocol): Command() { protocol.recvMoveDir(this->direction); }

void Move::execute(Game& game) { game.x += (2 * ((int)direction) - 1); }

// ----------------------- JUMP ----------------------

// Jump::Jump(): Command(id) {}


// ----------------------- DAMAGE ----------------------

// Damage::Damage(): Command(id) {}

// ----------------------- JOIN ----------------------

Join::Join(GameBrowser& gb, uint8_t& id_to_join, Queue<uint8_t>& game_state, std::atomic<bool>& connected_to_room):
        gb(gb), game_id(id_to_join), joined_game(connected_to_room), game_state(game_state) {}

void Join::execute() { gb.join_game(game_id, game_state, joined_game); }

// ----------------------- CREATE ----------------------

Create::Create(GameBrowser& gb, uint8_t& id_to_create, Queue<uint8_t>& game_state, std::atomic<bool>& connected_to_room):
        Join(gb, id_to_create, game_state, connected_to_room) {
    gb.create_game(id_to_create);
}
