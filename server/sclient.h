#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <atomic>
#include <memory>

#include <stdint.h>

#include "../common/queue.h"

#include "sprotocol.h"
#include "sreceiver.h"
#include "ssender.h"

class Game;
class LobbyClient;

namespace ServerSide {
class Client {
private:
    ServerSide::Protocol protocol;
    ServerSide::Receiver recv;
    ServerSide::Sender send;
    std::atomic<bool> killed;
    Queue<uint8_t> game_state;

public:
    const uint8_t id;

    explicit Client(Socket&& peer, GameBrowser& gb, uint8_t id);
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
