#include "acceptor.h"

#include <spdlog/spdlog.h>

#include "../common/liberror.h"

#include "sclient.h"
#include "sprotocol.h"

Acceptor::Acceptor(const char* servname): Thread(), skt(Socket(servname)) {}

void Acceptor::run() {
    uint8_t id = 0;
    do {

        try {
            spdlog::get("server")->debug("Esperando un cliente para aceptar");
            clients_connected[id] = std::make_unique<ServerSide::Client>(skt.accept(), gb, id);
            spdlog::get("server")->info("Cliente {:d} aceptado con exito", id);
            id++;
            reap_dead();

        } catch (const LibError& e) {
            if (_keep_running) {
                spdlog::get("server")->error("Ocurrio un error con el socket en acceptor");
            }
        }

    } while (this->_keep_running);
}

void Acceptor::kill() {
    this->stop();
    skt.shutdown(SHUTDOWN_RW);
    skt.close();
}

void Acceptor::reap_dead() {
    for (const auto& [id, client]: clients_connected) {
        if (not client->isAlive()) {
            clients_connected.erase(id);
            spdlog::get("server")->debug("Liberados los recursos del cliente {:d}", id);
        }
    }
}

Acceptor::~Acceptor() {
    if (_keep_running) {
        this->kill();
    }
}
