#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <atomic>
#include <memory>

#include <stdint.h>

#include "../common/States.h"
#include "../common/queue.h"

#include "game_loop.h"
#include "sprotocol.h"
#include "sreceiver.h"
#include "ssender.h"

namespace ServerSide {
class Client {
public:
    const uint8_t id;

private:
    ServerSide::Protocol protocol;
    ServerSide::Receiver recv;
    ServerSide::Sender send;
    std::atomic<bool> killed;
    Queue<std::shared_ptr<States>> state_queue;

public:
    explicit Client(Socket&& peer, GameBrowser& browser, const uint8_t& id);
    /*
        Retorna si ambos hilos estan 'vivos'
    */
    bool isAlive();
    /*
        Detiene los hilos recv y send de forma forzosa y (en un supuesto caso) de forma 'gentil'
    */
    void stop();
    /*
        Termina de forma forzosa los threads send y receive
    */
    void kill();

    ~Client();
};
}  // namespace ServerSide

#endif
