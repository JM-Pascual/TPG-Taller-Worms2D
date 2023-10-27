#include "acceptor.h"

#include <spdlog/spdlog.h>

#include "../common/liberror.h"

#include "sclient.h"
#include "sprotocol.h"

Acceptor::Acceptor(const char* servname): Thread(), skt(Socket(servname)), killed(false) {}

Acceptor::~Acceptor() {
    if (not killed) {
        this->kill();
    }
    gb.killAll();
}

void Acceptor::run() {
    try {
        uint8_t id = 0;
        do {
            spdlog::get("server")->debug("Esperando un cliente para aceptar");
            waiting_clients[id] = std::make_unique<ServerSide::Client>(skt.accept(), gb, id);
            spdlog::get("server")->info("Cliente {:d} aceptado con exito", id);
            id++;
        } while (this->_keep_running);

    } catch (const LibError& e) {
        if (not killed) {
            spdlog::get("server")->error("Ocurrio un error con el socket en acceptor");
        }
    }
}

void Acceptor::kill() {
    this->killed = true;
    this->stop();
    skt.shutdown(SHUTDOWN_RW);
}
