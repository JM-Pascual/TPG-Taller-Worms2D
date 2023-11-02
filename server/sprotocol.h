#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <memory>

#include <stdint.h>

#include "../common/const.h"
#include "../common/socket.h"

class GameState;
class Vector2D;

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

    /*
        Recibe data chequeando si se cierra el socket
    */
    void recv(void* data, unsigned int sz);
    /*
        Envia data chequeando si se cierra el socket
    */
    void send(const void* data, unsigned int sz);
    /*
        Recibe un int de 8 bits sin signo
    */
    uint8_t recvUint8();

    void sendPosition(const Vector2D& pos);

public:
    void sendGameState(const std::shared_ptr<GameState>& game_state);
    /*
        Construye el protocolo y su respectivo socket
    */
    explicit Protocol(Socket&& peer);
    /*
        Recibe el comando que el cliente desea ejecutar
    */
    void recvCommand(Actions&);
    /*
        Recibe la direccion hacia la cual se debe mover el gusano
    */
    void recvDirection(MoveDir&);
    /*
        Cierra forzosamente el socket del protocolo (en caso de que no se haya hecho)
    */
    void close();
    /*
        Recibe la id del game al que se quiere conectar el cliente
    */
    void recvGameID(uint8_t&);
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
