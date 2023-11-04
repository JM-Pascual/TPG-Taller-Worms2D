#include "cprotocol.h"

#include <cerrno>
#include <cstring>

#include <arpa/inet.h>

#include "../common/GameState.h"
#include "../common/liberror.h"

void ClientSide::Protocol::send(const void* data, unsigned int sz) {
    unsigned int sz_sent = skt.sendall(data, sz, &send_was_closed);

    if (sz_sent == 0 || send_was_closed) {
        throw LibError(errno, "se cerro la conexion con el servidor");
    }
}

void ClientSide::Protocol::recv(void* data, unsigned int sz) {
    unsigned int sz_recv = skt.recvall(data, sz, &recv_was_closed);

    if (sz_recv == 0 || recv_was_closed) {
        throw LibError(errno, "se cerro la conexion con el servidor");
    }
}

void ClientSide::Protocol::recvCommand(Actions& c) { c = (Actions)recvUint8(); }

uint8_t ClientSide::Protocol::recvUint8() {
    uint8_t i;
    recv(&i, sizeof(uint8_t));
    return i;
}

float ClientSide::Protocol::recvFloat() {
    uint32_t raw_bits;
    recv(&raw_bits, sizeof(uint32_t));
    raw_bits = ntohl(raw_bits);
    float float_value;
    memcpy(&float_value, &raw_bits, sizeof(uint32_t));
    return float_value;
}

bool ClientSide::Protocol::recvBool() {
    bool bool_net;
    recv(&bool_net, sizeof(bool));
    bool bool_final = ntohl(bool_net);
    return bool_final;
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
    float x = meter_to_pixel_x(recvFloat());
    float y = meter_to_pixel_y(recvFloat());
    bool is_wa = recvBool();
    bool direction = recvBool();
    return std::make_shared<PlayerState>(x, y, is_wa, direction);
}

float ClientSide::Protocol::meter_to_pixel_x(float meter_position) {
    return (meter_position * PPM);
}

float ClientSide::Protocol::meter_to_pixel_y(float meter_position) {
    return (720 - meter_position * PPM); //ToDo
}