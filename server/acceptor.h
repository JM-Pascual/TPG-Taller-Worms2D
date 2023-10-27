#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <atomic>
#include <map>
#include <memory>

#include "../common/socket.h"
#include "../common/thread.h"

#include "lobby.h"

namespace ServerSide {
class Protocol;
}

#define SHUTDOWN_RW 2

class Acceptor: public Thread {

private:
    Socket skt;
    GameBrowser gb;
    std::atomic<bool> killed;
    std::map<uint8_t, std::unique_ptr<ServerSide::Client>> waiting_clients;

public:
    explicit Acceptor(const char* servname);

    void run() override;

    void kill();

    ~Acceptor();
    /*
     *  No queremos ni copiar ni mover el acceptor
     */
    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

    Acceptor(Acceptor&&) = delete;
    Acceptor& operator=(Acceptor&&) = delete;
};

#endif
