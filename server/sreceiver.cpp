#include "sreceiver.h"

#include "../common/dto.h"

#include "command.h"
#include "game.h"
#include "game_browser.h"
#include "sparser.h"
#include "sprotocol.h"

ServerSide::Receiver::Receiver(ServerSide::Protocol& protocol, GameBrowser& gb,
                               Queue<std::shared_ptr<Dto>>& game_state):
        protocol(protocol),
        gb(gb),
        connected_to_room(false),
        room_id(255),
        game_state(game_state) {}

void ServerSide::Receiver::run() {
    Commands c;
    do {
        while (not connected_to_room) {
            protocol.recvCommand(c);
            ServerSide::Parser::makeLobbyCommand(c, protocol, gb, connected_to_room, room_id,
                                                 game_state)
                    ->execute();
        }

        Queue<std::shared_ptr<Command>>& q = gb.getQueue(room_id);

        while (connected_to_room) {
            protocol.recvCommand(c);
            q.push(ServerSide::Parser::makeGameCommand(c, protocol));
        }

    } while (_keep_running);
}

void ServerSide::Receiver::kill() { this->_is_alive = false; }
