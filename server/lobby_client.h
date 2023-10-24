#ifndef LOBBY_CLIENT_H
#define LOBBY_CLIENT_H

#include <atomic>

#include <stdint.h>

#include "../common/thread.h"

#include "sclient.h"
#include "sprotocol.h"

class Lobby;
class Socket;

class LobbyClient: public Thread {


private:
    ServerSide::Protocol protocol;
    Lobby& lobby;
    std::atomic<bool> killed;

public:
    friend class ServerSide::Client;

    const uint8_t id;  // id de solo lectura
    /*
        Inicializa los atributos de LobbyClient
    */
    explicit LobbyClient(Socket&&, Lobby&, const uint8_t);
    /*

    */
    void run() override;
    /*
        Cierra el protocolo y setea killed en true para saber si fue intencional
    */
    void kill();
    /*
        Destructor default ya que no hay que liberar ningun recurso que no este en stack
    */
    ~LobbyClient() override = default;
};


#endif
