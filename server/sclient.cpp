#include "sclient.h"

#include <utility>

#include "game.h"
#include "lobby_client.h"

ServerSide::Client::Client(LobbyClient* lc, std::unique_ptr<Game>& game):
        protocol(std::move(lc->protocol)),
        recv(this->protocol, game),
        send(this->protocol, game),
        killed(false),
        id(lc->id) {
    recv.start();
    send.start();
}

ServerSide::Client::Client(Socket&& peer, std::unique_ptr<Game>& game, const uint8_t id):
        protocol(std::move(peer)),
        recv(this->protocol, game),
        send(this->protocol, game),
        killed(false),
        id(id) {
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
