#include "command.h"

#include "game_browser.h"
#include "sprotocol.h"

// ----------------------- COMMAND ----------------------

// ----------------------- NULL_COMMAND ----------------------

void NullCommand::execute() {}

// ----------------------- MOVE ----------------------

Move::Move(ServerSide::Protocol& protocol): Command() { protocol.recvMoveDir(this->direction); }

void Move::execute() {}  // Saque la simulacion

// ----------------------- JUMP ----------------------

// Jump::Jump(): Command(id) {}


// ----------------------- DAMAGE ----------------------

// Damage::Damage(): Command(id) {}

// ----------------------- JOIN ----------------------

Join::Join(GameBrowser& gb, uint8_t& id_to_join):
        gb(gb), game_id(id_to_join) {}

void Join::execute() { gb.join_game(game_id); }
// ----------------------- CREATE ----------------------

Create::Create(GameBrowser& gb, uint8_t& id_to_create) : gb(gb), id_to_create(id_to_create) {}

void Create::execute() { gb.create_game(id_to_create); }
