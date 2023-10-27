#include "sclient.h"

#include <utility>

#include <spdlog/spdlog.h>

#include "game.h"


ServerSide::Client::Client(Socket&& peer, const GameBrowser& gb, const uint8_t id):
        protocol(std::move(peer)),
        recv(this->protocol, gb),
        send(this->protocol, game_state),
        killed(false),
        id(id) {
    spdlog::get("server")->debug("Iniciando receptor en cliente {:d}", id);
    recv.start();
    spdlog::get("server")->debug("Iniciando sender en cliente {:d}", id);
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
    spdlog::get("server")->debug("Cerrando protocolo en cliente {:d}", id);
    protocol.close();
}

ServerSide::Client::~Client() {
    if (!killed) {
        this->kill();
    }
    spdlog::get("server")->debug("Joineando receptor en cliente {:d}", id);
    recv.join();
    spdlog::get("server")->debug("Joineando sender en cliente {:d}", id);
    send.join();
}
