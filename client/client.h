#ifndef CLIENT_H
#define CLIENT_H

#include "cprotocol.h"
#include "creceiver.h"
#include "csender.h"

class Client {

private:
    ClientSide::Receiver recv;
    ClientSide::Sender send;
    ClientSide::Protocol protocol;
    Queue<uint8_t> game_state_queue;
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
