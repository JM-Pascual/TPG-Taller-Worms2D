#include "sreceiver.h"

#include "command.h"
#include "game.h"
#include "game_browser.h"
#include "sparser.h"
#include "sprotocol.h"

ServerSide::Receiver::Receiver(ServerSide::Protocol& protocol, const GameBrowser& gb):
        protocol(protocol), gb(gb), joined_game(false) {}

void ServerSide::Receiver::run() {
    Commands o;
    ServerSide::Parser parser;
    Queue<uint8_t> game_queue;
    do {
        while (not joined_game) {
            protocol.recvCommand(o);
            parser.makeLobbyCommand(o, protocol, 1, gb, joined_game, game_queue)->execute();
        }


    } while (_keep_running);
}

void ServerSide::Receiver::kill() { this->_is_alive = false; }
