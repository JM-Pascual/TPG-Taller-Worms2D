#include "cprotocol.h"

#include <cstring>
#include <vector>

#include <arpa/inet.h>
#include <errno.h>
#include <stdint.h>

#include "../common/GameState.h"
#include "../common/liberror.h"

void ClientSide::Protocol::send(const void* data, unsigned int sz) {
    unsigned int sz_sent = skt.sendall(data, sz, &send_was_closed);

    if (sz_sent == 0 || send_was_closed) {
        throw LibError(errno, "El sv cerro el socket");
    }
}

void ClientSide::Protocol::recv(void* data, unsigned int sz) {
    unsigned int sz_recv = skt.recvall(data, sz, &recv_was_closed);

    if (sz_recv == 0 || recv_was_closed) {
        throw LibError(errno, "El sv cerro el socket");
    }
}

void ClientSide::Protocol::recvCommand(Actions& c) { c = (Actions)recvUint8(); }

uint8_t ClientSide::Protocol::recvUint8() {
    uint8_t i;
    recv(&i, sizeof(uint8_t));
    return i;
}

float ClientSide::Protocol::recvFloat() {
    uint32_t i;
    recv(&i, sizeof(uint32_t));
    i = ntohl(i);

    std::vector<char> x;
    x.resize(sizeof(float));
    memcpy(x.data(), &i, sizeof(float));

    float f;
    memcpy(&f, x.data(), sizeof(float));
    return f;
}

bool ClientSide::Protocol::recvBool() {
    bool b;
    recv(&b, sizeof(bool));
    return b;
}

ClientSide::Protocol::Protocol(const char* hostname, const char* servname):
        skt(hostname, servname), send_was_closed(false), recv_was_closed(false) {}

void ClientSide::Protocol::close() {
    if (not(send_was_closed || recv_was_closed)) {
        this->skt.shutdown(SHUT_RDWR);
        this->skt.close();
    }
}

std::shared_ptr<GameState> ClientSide::Protocol::recvGameState() {
    return std::make_shared<GameState>(recvFloat(), recvFloat(), recvBool(), recvBool());
}
