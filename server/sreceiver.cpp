#include "sreceiver.h"

#include "lobby.h"
#include "sprotocol.h"

ServerSide::Receiver::Receiver(ServerSide::Protocol* protocol, Lobby* lobby):
        protocol(protocol), lobby(lobby) {}

void ServerSide::Receiver::run() {
    uint8_t o;
    do {
        protocol->recv(&o, 1);
        lobby->notifyAllClients(o);
    } while (_keep_running);
}

void ServerSide::Receiver::kill() { this->_is_alive = false; }
