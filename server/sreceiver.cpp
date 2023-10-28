#include "sreceiver.h"

#include "command.h"
#include "game.h"
#include "game_browser.h"
#include "sparser.h"
#include "sprotocol.h"

ServerSide::Receiver::Receiver(ServerSide::Protocol& protocol, GameBrowser& gb):
        protocol(protocol), gb(gb), connected_to_room(false) {}

void ServerSide::Receiver::run() {
    Commands o;
    do {
        while (not connected_to_room) {
            protocol.recvCommand(o);
            ServerSide::Parser::makeLobbyCommand(o, protocol, gb, connected_to_room, room_id)->execute();
        }
        Queue<std::shared_ptr<Command>>& q = gb.getQueue(room_id);
        while (connected_to_room) {
            protocol.recvCommand(o);
            q.push(ServerSide::Parser::makeGameCommand(o, protocol));
        }

    } while (_keep_running);
}

void ServerSide::Receiver::kill() { this->_is_alive = false; }
