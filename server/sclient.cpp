#include "sclient.h"

#include <utility>

#include "game.h"

ServerSide::Client::Client(Socket&& peer, Game* lobby):
        protocol(std::move(peer)),
        recv(this->protocol, lobby),
        send(this->protocol, lobby),
        killed(false) {
    recv.start();
    send.start();
}

const bool ServerSide::Client::isAlive() { return (recv.is_alive() && send.is_alive()); }

void ServerSide::Client::sendChat(const uint8_t& dto) { send.queueUp(dto); }

void ServerSide::Client::stop() {
    recv.stop();
    send.stop();
}

void ServerSide::Client::kill() {
    killed = true;
    this->stop();
    send.kill();
    recv.kill();
    protocol.close();
}

ServerSide::Client::~Client() {
    if (!killed) {
        this->kill();
    }
    recv.join();
    send.join();
}
