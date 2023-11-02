#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <memory>

#include <stdint.h>

#include "../common/const.h"
#include "../common/socket.h"

#include "Action.h"

class GameState;

namespace ClientSide {
class Protocol {

private:
    Socket skt;
    /*
        Los separo en dos bool y no en uno atomic ya que el socket necesita un *bool. Podria usar
        load de atomic pero estaria en la misma situacion que en un solo bool normal.
    */
    bool send_was_closed;
    bool recv_was_closed;
    /*
        Recibe data chequeando si se cierra el socket
    */
    void recv(void* data, unsigned int sz);


    uint8_t recvUint8();


    float recvFloat();

    bool recvBool();

public:
    // Envia data chequeando si se cierra el socket
    void send(const void* data, unsigned int sz);

    void recvCommand(Actions& c);
    /*
        Construye el protocolo y su respectivo socket
    */
    explicit Protocol(const char* hostname, const char* servname);
    /*
        Cierra forzosamente el socket del protocolo (en caso de que no se haya hecho)
    */
    void close();

    std::shared_ptr<GameState> recvGameState();
    /*
        No tiene sentido ni copiar ni mover el protocolo
    */
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    Protocol(Protocol&&) = delete;
    Protocol& operator=(Protocol&&) = delete;
};
}  // namespace ClientSide

#endif
