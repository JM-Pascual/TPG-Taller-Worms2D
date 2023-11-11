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

void ServerSide::Protocol::sendPosition(const b2Vec2& pos) {
    uint32_t x_net;
    memcpy(&x_net, &pos.x, sizeof(uint32_t));
    x_net = htonl(x_net);
    send(&x_net, sizeof(uint32_t));

    uint32_t y_net;
    memcpy(&y_net, &pos.y, sizeof(uint32_t));
    y_net = htonl(y_net);
    send(&y_net, sizeof(uint32_t));
}

void ServerSide::Protocol::sendPlayerCount(const std::shared_ptr<GameState>& count) {
    std::shared_ptr<PlayerCount> p = std::dynamic_pointer_cast<PlayerCount>(count);
    send(&p->tag, sizeof(uint8_t));
    send(&p->quantity, sizeof(uint8_t));
}

void ServerSide::Protocol::sendPlayerState(const std::shared_ptr<GameState>& ps) {
    std::shared_ptr<PlayerState> p = std::dynamic_pointer_cast<PlayerState>(ps);

    send(&p->tag, sizeof(uint8_t));
    this->sendPosition(p->pos);
    send(&p->is_walking, sizeof(bool));
    send(&p->is_jumping, sizeof(bool));
    send(&p->is_backflipping, sizeof(bool));
    send(&p->facing_right, sizeof(bool));

    uint32_t inclination_net;
    memcpy(&inclination_net, &p->aim_inclination_degrees, sizeof(uint32_t));
    inclination_net = htonl(inclination_net);
    send(&inclination_net, sizeof(uint32_t));
}

void ServerSide::Protocol::sendProyectileCount(const std::shared_ptr<GameState>& count) {
    std::shared_ptr<ProyectileCount> p = std::dynamic_pointer_cast<ProyectileCount>(count);
    send(&p->tag, sizeof(uint8_t));
    send(&p->quantity, sizeof(uint8_t));
}

void ServerSide::Protocol::sendProyectileState(const std::shared_ptr<GameState>& ps) {
    std::shared_ptr<ProyectileState> p = std::dynamic_pointer_cast<ProyectileState>(ps);
    send(&p->tag, sizeof(uint8_t));
    this->sendPosition(p->pos);
    send(&p->type, sizeof(uint8_t));
    send(&p->impacted, sizeof(bool));
}

void ServerSide::Protocol::sendGameState(const std::shared_ptr<GameState>& game_state) {
    switch (game_state->tag) {
        case GameStateTag::BATTLEFIELD:
            break;

        case GameStateTag::PLAYER_COUNT:
            sendPlayerCount(game_state);
            break;

        case GameStateTag::PLAYER:
            sendPlayerState(game_state);
            break;


        case GameStateTag::PROYECTILE_COUNT:
            sendProyectileCount(game_state);
            break;

        case GameStateTag::PROYECTILE:
            sendProyectileState(game_state);
            break;

        default:
            break;
    }
}
