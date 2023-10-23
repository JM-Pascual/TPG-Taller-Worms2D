#include "sreceiver.h"

#include "command.h"
#include "game.h"
#include "sparser.h"
#include "sprotocol.h"

ServerSide::Receiver::Receiver(ServerSide::Protocol& protocol, Game* lobby):
        protocol(protocol), lobby(lobby), x(0) {}

void ServerSide::Receiver::run() {
    Commands o;
    ServerSide::Parser parser;
    do {
        protocol.recvCommand(o);
        parser.makeCommand(o, protocol).get()->execute(x);

        lobby->notifyAllClients(x);
    } while (_keep_running);
}

void ServerSide::Receiver::kill() { this->_is_alive = false; }
