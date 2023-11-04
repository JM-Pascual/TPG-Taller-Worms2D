#ifndef CLIENT_H
#define CLIENT_H

#include <memory>

#include "cprotocol.h"
#include "creceiver.h"
#include "csender.h"

class Action;
class WormGameState;

class Client {

private:
    ClientSide::Protocol protocol;
    ClientSide::Receiver recv;
    ClientSide::Sender send;
    Queue<std::shared_ptr<WormGameState>> game_state_queue;
    Queue<std::shared_ptr<Action>> action_queue;

public:
    /*
        Construye el cliente con su protocolo
    */
    explicit Client(const char* hostname, const char* servname);
    /*
        Corre el cliente
    */
    void run();

    ~Client();
};


#endif
