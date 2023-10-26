#include "command.h"

#include "lobby.h"
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

Join::Join(Lobby& lobby, uint8_t id, uint8_t game_id):
        lobby(lobby), game_id(game_id), client_id(id) {}

void Join::execute() { lobby.joinGame(game_id, client_id); }
// ----------------------- CREATE ----------------------

Create::Create(uint8_t id, Lobby& lobby): Join(lobby, id, lobby.createGame()) {
    /*
        Recibe nombre de la sala, mapa y ...
        Pienso que quedaria de la forma
        (atributo de Create) uint8_t game_id = lobby.create_game(args)
    */
}
