#ifndef LOBBY_CLIENT_H
#define LOBBY_CLIENT_H

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

public:
    friend class ServerSide::Client;

    const uint8_t id;

    explicit LobbyClient(Socket&&, Lobby&, const uint8_t);

    void run() override;
};


#endif
