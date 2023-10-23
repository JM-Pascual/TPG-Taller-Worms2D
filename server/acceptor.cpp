#include "acceptor.h"

#include "../common/liberror.h"

#include "lobby_client.h"
#include "sclient.h"
#include "sprotocol.h"

Acceptor::Acceptor(const char* servname):
        Thread(), skt(Socket(servname)), cleaner(), killed(false) {
    // cleaner.start();
}

Acceptor::~Acceptor() {
    if (!killed) {
        this->kill();
    }
    lobby.killAll();
    // cleaner.kill();
    // cleaner.join();
}


void Acceptor::run() {
    try {
        uint8_t id = 0;
        do {
            lobby.pushLobbyClient(std::make_unique<LobbyClient>(skt.accept(), lobby, id), id);
            id++;
        } while (this->_keep_running);

    } catch (const LibError& e) {
        if (not killed) {
            std::cerr << e.what() << " en acceptor";
        }
    }
}

void Acceptor::kill() {
    this->killed = true;
    this->stop();
    skt.shutdown(SHUTDOWN_RW);
}
