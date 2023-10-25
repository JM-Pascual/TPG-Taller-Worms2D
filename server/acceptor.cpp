#include "acceptor.h"

#include <spdlog/spdlog.h>

#include "../common/liberror.h"

#include "lobby_client.h"
#include "sclient.h"
#include "sprotocol.h"

Acceptor::Acceptor(const char* servname): Thread(), skt(Socket(servname)), killed(false) {}

Acceptor::~Acceptor() {
    if (not killed) {
        this->kill();
    }
    lobby.killAll();
}


void Acceptor::run() {
    try {
        uint8_t id = 0;
        do {
            spdlog::get("server")->debug("Esperando un cliente para aceptar");
            lobby.pushLobbyClient(std::make_unique<LobbyClient>(skt.accept(), lobby, id), id);
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
