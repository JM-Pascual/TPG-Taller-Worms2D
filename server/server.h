#ifndef CLIENT_H
#define CLIENT_H

#include <memory>

#include "acceptor.h"
#include "sprotocol.h"
#include "sreceiver.h"
#include "ssender.h"

class Server {

private:
    Acceptor acceptor;

public:
    /*
        Crea el servidor junto a su protocolo
    */
    explicit Server(char* servname);
    /*
        Corre el servidor
    */
    void run();
    /*
        Libera la memoria alocada de acceptor
    */
    ~Server();
    /*
        No tiene sentido ni copiar ni mover el servidor
    */
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;
};


#endif
