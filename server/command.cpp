#include "command.h"

#include "sprotocol.h"

Command::Command(uint8_t id): client_id(id) {}

Move::Move(uint8_t id, ServerSide::Protocol& protocol): Command(id) {
    protocol.recvMoveDir(this->direction);
}

void Move::execute(uint8_t& x) { x += 2 * (uint8_t)direction - 1; }

// Jump::Jump(uint8_t id): Command(id) {}

// Damage::Damage(uint8_t id): Command(id) {}

Create::Create(uint8_t id, ServerSide::Protocol& protocol, GameBrowser& lobby,
               std::unique_ptr<LobbyClient>& client):
        Command(id), lobby(lobby), client(client) {
    /*
        Recibe nombre de la sala, mapa y ...
        Pienso que quedaria de la forma
        (atributo de Create) uint8_t game_id = lobby.create_game(args)
    */
    game_id = lobby.create_game();
}

void Create::execute(uint8_t& d) { lobby.join_game(game_id, client); }
