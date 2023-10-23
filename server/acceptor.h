#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <atomic>
#include <memory>

#include "../common/socket.h"
#include "../common/thread.h"

#include "cleaner.h"
#include "game_browser.h"

namespace ServerSide {
class Protocol;
}

#define SHUTDOWN_RW 2

class Acceptor: public Thread {

private:
    Socket skt;
    Cleaner cleaner;
    GameBrowser lobby;
    std::atomic<bool> killed;

public:
    explicit Acceptor(const char* servname);

    void run() override;

    void kill();

    ~Acceptor();
};

#endif
