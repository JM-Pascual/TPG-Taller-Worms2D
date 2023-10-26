#include "sprotocol.h"

#include <utility>

#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>

#include "../common/const.h"
#include "../common/liberror.h"

ServerSide::Protocol::Protocol(Socket&& peer):
        peer(std::move(peer)), send_was_closed(false), recv_was_closed(false) {}

ServerSide::Protocol::Protocol(Protocol&& p):
        peer(std::move(p.peer)),
        send_was_closed(p.send_was_closed),
        recv_was_closed(p.recv_was_closed) {}


void ServerSide::Protocol::send(const void* data, unsigned int sz) {
    unsigned int sz_sent = peer.sendall(data, sz, &send_was_closed);

    if (sz_sent == 0 || send_was_closed) {
        throw LibError(errno, "El cliente cerro el socket");
    }
}

void ServerSide::Protocol::recv(void* data, unsigned int sz) {
    unsigned int sz_recv = peer.recvall(data, sz, &recv_was_closed);

    if (sz_recv == 0 || recv_was_closed) {
        throw LibError(errno, "El cliente cerro el socket");
    }
}


void ServerSide::Protocol::close() {
    if (not(send_was_closed || recv_was_closed)) {
        this->peer.shutdown(SHUT_RDWR);
        this->peer.close();
    }
}

void ServerSide::Protocol::recvGameID(uint8_t& id) { id = this->recvUint8(); }


uint8_t ServerSide::Protocol::recvUint8() {
    uint8_t n;
    this->recv(&n, sizeof(uint8_t));
    return n;
}

void ServerSide::Protocol::recvCommand(Commands& c) { c = (Commands)this->recvUint8(); }

void ServerSide::Protocol::recvMoveDir(MoveDir& d) { d = (MoveDir)this->recvUint8(); }
