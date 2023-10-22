#ifndef SERVER_CLIENT_H
#define SERVER_CLIENT_H

#include <atomic>

#include "sprotocol.h"
#include "sreceiver.h"
#include "ssender.h"

class Lobby;

namespace ServerSide {
class Client {
private:
    ServerSide::Protocol protocol;
    ServerSide::Receiver recv;
    ServerSide::Sender send;
    std::atomic<bool> killed;

public:
    explicit Client(Socket&& peer, Lobby* lobby);
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
