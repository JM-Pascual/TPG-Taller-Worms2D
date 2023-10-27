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

Join::Join(GameBrowser& gb, uint8_t id, uint8_t game_id, Queue<uint8_t>& game_queue):
        gb(gb), game_id(game_id), client_id(id), game_queue(game_queue) {}

void Join::execute() { game_queue = gb.join_game(game_id, client_id); }
// ----------------------- CREATE ----------------------

Create::Create(uint8_t id, GameBrowser& gb, Queue<uint8_t>& game_queue):
        Join(gb, id, gb.create_game(), game_queue) {
    /*
        Recibe nombre de la sala, mapa y ...
        Pienso que quedaria de la forma
        (atributo de Create) uint8_t game_id = lobby.create_game(args)
    */
}
