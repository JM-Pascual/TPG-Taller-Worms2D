#include "sprotocol.h"

#include <utility>
#include <vector>

#include <arpa/inet.h>
#include <errno.h>
#include <spdlog/spdlog.h>
#include <stdint.h>

#include "../common/GameState.h"
#include "../common/const.h"
#include "../common/liberror.h"

float ReverseFloat(const float inFloat) {
    float retVal;
    char* floatToConvert = (char*)&inFloat;
    char* returnFloat = (char*)&retVal;

    // swap the bytes into a temporary buffer
    returnFloat[0] = floatToConvert[3];
    returnFloat[1] = floatToConvert[2];
    returnFloat[2] = floatToConvert[1];
    returnFloat[3] = floatToConvert[0];

    return retVal;
}

ServerSide::Protocol::Protocol(Socket&& peer):
        peer(std::move(peer)), send_was_closed(false), recv_was_closed(false) {}

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

// ------------------------------ RECEIVE ----------------------------------

void ServerSide::Protocol::recvGameID(uint8_t& id) { id = this->recvUint8(); }

uint8_t ServerSide::Protocol::recvUint8() {
    uint8_t n;
    this->recv(&n, sizeof(uint8_t));
    return n;
}

void ServerSide::Protocol::recvCommand(Actions& c) { c = (Actions)this->recvUint8(); }

void ServerSide::Protocol::recvDirection(MoveDir& d) { d = (MoveDir)this->recvUint8(); }

// ------------------------------ SEND -----------------------------------

void ServerSide::Protocol::sendPosition(const PlayerPosition& pos) {
    uint32_t i;
    memcpy(&i, &pos.x, sizeof(float));
    i = htonl(i);
    send(&i, sizeof(float));

    // int32_t y = htonl(pos.y);
    // send(&y, sizeof(int32_t));
}

void ServerSide::Protocol::sendGameState(const std::shared_ptr<GameState>& game_state) {

    this->sendPosition(game_state->player_position);
    // send(&game_state->is_walking, sizeof(uint8_t));
    // send(&game_state->direction, sizeof(uint8_t));
}
