#include "sprotocol.h"

#include <iostream>
#include <utility>
#include <vector>

#include <arpa/inet.h>
#include <errno.h>
#include <spdlog/spdlog.h>
#include <stdint.h>

#include "../common/GameState.h"
#include "../common/const.h"
#include "../common/liberror.h"
#include "../common/vector2d.h"

ServerSide::Protocol::Protocol(Socket&& peer):
        peer(std::move(peer)), send_was_closed(false), recv_was_closed(false) {}

void ServerSide::Protocol::send(const void* data, unsigned int sz) {
    unsigned int sz_sent = peer.sendall(data, sz, &send_was_closed);

    if (sz_sent == 0 || send_was_closed) {
        throw LibError(errno, "se cerro la conexion con el cliente");
    }
}

void ServerSide::Protocol::recv(void* data, unsigned int sz) {
    unsigned int sz_recv = peer.recvall(data, sz, &recv_was_closed);

    if (sz_recv == 0 || recv_was_closed) {
        throw LibError(errno, "se cerro la conexion con el cliente");
    }
}


void ServerSide::Protocol::close() {
    if (not(send_was_closed || recv_was_closed)) {
        this->peer.shutdown(SHUT_RDWR);
        this->peer.close();
    }
}

// ------------------------------ RECEIVE ----------------------------------

void ServerSide::Protocol::recvGameID(uint8_t& id) { id = this->recvUint8(); }

uint8_t ServerSide::Protocol::recvUint8() {
    uint8_t n;
    this->recv(&n, sizeof(uint8_t));
    return n;
}

void ServerSide::Protocol::recvCommand(Actions& c) { c = (Actions)this->recvUint8(); }

void ServerSide::Protocol::recvDirection(Direction& d) { d = (Direction)this->recvUint8(); }

void ServerSide::Protocol::recvJumpDir(JumpDir& dir) { dir = (JumpDir)this->recvUint8(); }

void ServerSide::Protocol::recvADSAngleDir(ADSAngleDir& dir) {
    dir = (ADSAngleDir)this->recvUint8();
}

void ServerSide::Protocol::recvDelay(DelayAmount& amount) {
    amount = (DelayAmount)this->recvUint8();
}

void ServerSide::Protocol::recvGadget(WeaponsAndTools& gadget) {
    gadget = (WeaponsAndTools)this->recvUint8();
}

// ------------------------------ SEND -----------------------------------

void ServerSide::Protocol::sendPosition(const Vector2D& pos) {

    uint32_t x_net;
    memcpy(&x_net, &pos.x, sizeof(uint32_t));
    x_net = htonl(x_net);
    send(&x_net, sizeof(uint32_t));

    uint32_t y_net;
    memcpy(&y_net, &pos.y, sizeof(uint32_t));
    y_net = htonl(y_net);
    send(&y_net, sizeof(uint32_t));
}

void ServerSide::Protocol::sendGameState(const std::shared_ptr<GameState>& game_state) {
    this->sendPosition(game_state->player_position);
    send(&game_state->is_walking, sizeof(bool));
    send(&game_state->facing_right, sizeof(bool));
}
