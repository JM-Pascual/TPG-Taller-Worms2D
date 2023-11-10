#include "sclient.h"

#include <utility>

#include <spdlog/spdlog.h>

#include "game_loop.h"


ServerSide::Client::Client(Socket&& peer, GameBrowser& browser, const uint8_t id):
        protocol(std::move(peer)),
        recv(this->protocol, browser, state_queue, id),
        send(this->protocol, state_queue),
        killed(false),
        id(id) {
    spdlog::get("server")->debug("Iniciando receptor en cliente {:d}", id);
    recv.start();
    spdlog::get("server")->debug("Iniciando sender en cliente {:d}", id);
    send.start();
    state_queue.push(std::make_shared<MyID>(id));
}

bool ServerSide::Client::isAlive() { return (recv.is_alive() && send.is_alive()); }

void ServerSide::Client::stop() {
    recv.stop();
    send.stop();
}

void ServerSide::Client::kill() {
    spdlog::get("server")->debug("Matando cliente {:d}", id);
    killed = true;
    this->stop();
    state_queue.close();
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
