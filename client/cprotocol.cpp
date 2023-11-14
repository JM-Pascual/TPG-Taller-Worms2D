#include "cprotocol.h"

#include <cerrno>
#include <cstring>
#include <vector>

#include <arpa/inet.h>

#include "../common/States.h"
#include "../common/const.h"
#include "../common/liberror.h"

void ClientSide::Protocol::send(const void* data, unsigned int sz) {
    unsigned int sz_sent = skt.sendall(data, sz, &send_was_closed);

    if (sz_sent == 0 || send_was_closed) {
        throw LibError(errno, "se cerro la conexion con el servidor");
    }
}

void ClientSide::Protocol::sendString64(const std::string& str) {
    uint8_t length = str.length();
    this->send(&length, sizeof(uint8_t));
    this->send(str.data(), length);
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

std::shared_ptr<States> ClientSide::Protocol::recvStates() {
    StatesTag tag = (StatesTag)recvUint8();

    switch (tag) {
        case StatesTag::MY_ID:
            return std::make_shared<MyID>(recvUint8());

        case StatesTag::GAME_NOT_JOINABLE:
            return std::make_shared<GameNotJoinable>(recvUint8());

        case StatesTag::GAMES_COUNT_L:
            return std::make_shared<GamesCountL>(recvUint8());

        case StatesTag::INFO_GAME_L:
            return recvGameInfo();

        case StatesTag::PLAYER_COUNT_L:
            return std::make_shared<PlayerCountL>(recvUint8());

        case StatesTag::PLAYER_L:
            return std::make_shared<PlayerStateL>(recvBool(), recvUint8());

        case StatesTag::BATTLEFIELD_G:
            return std::make_shared<PlayerCountG>(recvUint8());

        case StatesTag::PLAYER_G:
            return recvPlayerGame();

        case StatesTag::PROJECTILE_G:
            return recvProjectileGame();


        case StatesTag::PROJECTILE_COUNT_G:
            return std::make_shared<ProjectileCountG>(recvUint8());

        case StatesTag::PLAYER_COUNT_G:
            return std::make_shared<PlayerCountG>(recvUint8());

        default:
            return std::make_shared<PlayerCountG>(recvUint8());  // ToDo placeholder para un default
    }
}

float ClientSide::Protocol::meter_to_pixel_x(float meter_position) {
    return (meter_position * PPM);
}

float ClientSide::Protocol::meter_to_pixel_y(float meter_position) {
    return (720 - meter_position * PPM);  // ToDo
}

void ClientSide::Protocol::recvString64(std::string& str) {
    uint8_t length;
    this->recv(&length, sizeof(uint8_t));

    std::vector<char> str_net;
    str_net.resize(length + 1);  // length + '\0'
    this->recv(str_net.data(), length);
    str = std::string(str_net.data());
}

std::shared_ptr<GameInfoL> ClientSide::Protocol::recvGameInfo() {
    std::string desc, map_name;

    recvString64(desc);
    recvString64(map_name);

    uint8_t p_count = recvUint8();
    uint8_t game_id = recvUint8();

    return std::make_shared<GameInfoL>(desc, map_name, p_count, game_id);
}

std::shared_ptr<PlayerStateG> ClientSide::Protocol::recvPlayerGame() {
    float x = meter_to_pixel_x(recvFloat());
    float y = meter_to_pixel_y(recvFloat());
    bool is_wa = recvBool();
    bool is_jumping = recvBool();
    bool is_backflipping = recvBool();
    bool direction = recvBool();
    bool was_hit = recvBool();
    float aim_inclination = recvFloat();
    float life = recvFloat();

    return std::make_shared<PlayerStateG>(x, y, is_wa, is_jumping, is_backflipping, direction, was_hit,
                                          aim_inclination,life);
}

std::shared_ptr<ProjectileStateG> ClientSide::Protocol::recvProjectileGame() {
    float x = meter_to_pixel_x(recvFloat());
    float y = meter_to_pixel_y(recvFloat());
    float angle = recvFloat();
    auto proyectile_type = (WeaponsAndTools)recvUint8();
    bool impacted = recvBool();
    return std::make_shared<ProjectileStateG>(x, y, proyectile_type, impacted, angle);
}
