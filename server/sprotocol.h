#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include "../common/socket.h"

namespace ServerSide {
class Protocol {

private:
    Socket peer;
    /*
        Los separo en dos bool y no en uno atomic ya que el socket necesita un *bool. Podria usar
        load de atomic pero estaria en la misma situacion que en un solo bool normal.
    */
    bool send_was_closed;
    bool recv_was_closed;

public:
    /*
        Envia data chequeando si se cierra el socket
    */
    void send(const void* data, unsigned int sz);
    /*
        Recibe data chequeando si se cierra el socket
    */
    void recv(void* data, unsigned int sz);
    /*
        Construye el protocolo y su respectivo socket
    */
    explicit Protocol(Socket&& peer);
    /*
        Cierra forzosamente el socket del protocolo (en caso de que no se haya hecho)
    */
    void close();
    /*
        No tiene sentido ni copiar ni mover el protocolo
    */
    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    Protocol(Protocol&&) = delete;
    Protocol& operator=(Protocol&&) = delete;
};
}  // namespace ServerSide

#endif
