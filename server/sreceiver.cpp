#include "sreceiver.h"

#include "command.h"
#include "game.h"
#include "sparser.h"
#include "sprotocol.h"

ServerSide::Receiver::Receiver(ServerSide::Protocol& protocol, std::unique_ptr<Game>& game):
        protocol(protocol), game(game), x(0) {}

void ServerSide::Receiver::run() {
    Commands o;
    ServerSide::Parser parser;
    do {
        protocol.recvCommand(o);
        parser.makeGameCommand(o, protocol).get()->execute(x);

        game->notifyAllClients(x);
    } while (_keep_running);
}

void ServerSide::Receiver::kill() { this->_is_alive = false; }
