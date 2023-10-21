#include "acceptor.h"

#include "../common/liberror.h"

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
        do {
            lobby.pushClient(new ServerSide::Client(skt.accept(), &lobby));
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
