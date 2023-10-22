#include "sreceiver.h"

#include "lobby.h"
#include "sprotocol.h"

ServerSide::Receiver::Receiver(ServerSide::Protocol* protocol, Lobby* lobby):
        protocol(protocol), lobby(lobby) {
        x = 0;
}

void ServerSide::Receiver::run() {
    uint8_t o;
    do {
        protocol->recv(&o, 1);

        if (o == 0) {
            x--;
        } else if (o == 1) {
            x++;
        }

        lobby->notifyAllClients(x);
    } while (_keep_running);
}

void ServerSide::Receiver::kill() { this->_is_alive = false; }
