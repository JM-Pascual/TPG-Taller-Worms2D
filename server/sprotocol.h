#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <memory>
#include <string>

#include <stdint.h>

#include "../common/const.h"
#include "../common/socket.h"
#include "box2d/b2_math.h"

#define PPM 33.33f  // pixel per meter ratio.

class States;

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

    void sendPosition(const b2Vec2& pos);

    void sendPlayerState(const std::shared_ptr<States>& ps);

    void sendWormState(const std::shared_ptr<States>& state);

    void sendGameInfo(const std::shared_ptr<States>& count);

    void sendCount(const std::shared_ptr<States>& count);

    void sendPlayerLobby(const std::shared_ptr<States>& count);

    void sendLevelBuild(const std::shared_ptr<States>& lb);

    void sendProjectileState(const std::shared_ptr<States>& ps);

    void sendFloat(float number);

    void sendTurn(const std::shared_ptr<States>& state);

    void sendBattlefield(const std::shared_ptr<States>& state);

    float pixel_to_meter_x(float pixel_position);
    float pixel_to_meter_y(float pixel_position);
    void sendCrate(const std::shared_ptr<States>& state);

public:
    void sendStates(const std::shared_ptr<States>& state);
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
    void recvDirection(Direction&);
    /*
        Recibe la direccion hacia la cual debe saltar el gusano
    */
    void recvJumpDir(JumpDir& dir);
    /*
        Recibe la direccion hacia la cual debe inclinar la mira el gusano
    */
    void recvADSAngleDir(ADSAngleDir& dir);
    /*
        Recibe la cantidad de retraso que tiene un proyectil apto
    */
    void recvDelay(DelayAmount& amount);
    /*
        Recibe el arma o herramienta que el gusano se debe equipar
    */
    void recvGadget(WeaponsAndTools& gadget);
    /*
        Cierra forzosamente el socket del protocolo (en caso de que no se haya hecho)
    */
    void close();
    /*
        Recibe un string de maximo 64 caracteres
    */
    void recvString64(std::string& desc);


    float recvFloat();


    void recvPosition(b2Vec2& position);
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
