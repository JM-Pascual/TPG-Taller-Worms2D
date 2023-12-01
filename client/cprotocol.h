#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <memory>
#include <string>

#include <stdint.h>

#include "../common/const.h"
#include "../common/socket.h"

#include "Action.h"

#define PPM 33.33f  // pixel per meter ratio.
#define GADGETS_QUANTITY 10

class States;
class GameInfoL;
class ProjectileStateG;
class LevelStateG;
class PlayerStateG;
class WormStateG;
class CrateState;

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


    float meter_to_pixel_x(const float& meter_position);
    float meter_to_pixel_y(const float& meter_position);

    std::shared_ptr<GameInfoL> recvGameInfo();

    std::shared_ptr<LevelStateG> recvLevelBuild();

    std::shared_ptr<PlayerStateG> recvPlayerGame();

    std::shared_ptr<ProjectileStateG> recvProjectileGame();

    std::shared_ptr<WormStateG> recvWormGame();

    std::shared_ptr<CrateState> recvCrate();

public:
    // Envia data chequeando si se cierra el socket
    void send(const void* data, unsigned int sz);

    void sendString64(const std::string& str);

    void sendFloat(const float& number);

    uint8_t recvUint8();

    float recvFloat();

    bool recvBool();

    void recvString64(std::string& str);

    void recvCommand(Actions& c);
    /*
        Construye el protocolo y su respectivo socket
    */
    explicit Protocol(const char* hostname, const char* servname);
    /*
        Cierra forzosamente el socket del protocolo (en caso de que no se haya hecho)
    */
    void close();

    std::shared_ptr<States> recvStates();
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
