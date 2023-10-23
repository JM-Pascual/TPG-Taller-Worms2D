#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <atomic>
#include <memory>

#include <stdint.h>

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

public:
    const uint8_t id;

    explicit Client(LobbyClient*, std::unique_ptr<Game>&);

    explicit Client(Socket&& peer, std::unique_ptr<Game>&, const uint8_t);
    /*
        Retorna si ambos hilos estan 'vivos'
    */
    const bool isAlive();
    /*
        Envia al chat del cliente el mensaje incluido en el DTO
    */
    void sendChat(const uint8_t& dto);
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
