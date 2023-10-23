#ifndef WORMS2D_LOBBY_H
#define WORMS2D_LOBBY_H

#include <iostream>
#include <cstdint>
#include <map>

#include "game.h"
#include "../common/queue.h"
#include "sclient.h"

class Lobby {
private:
    std::map<uint8_t,Game*> games;
    std::mutex m;
public:
    Lobby();
    //Ver si está bien usar void o tengo que devolver la partida creada o a la que me uno para poder acceder más fácil
    void create_game(uint8_t game_code,ServerSide::Client* client); //Ver si paso puntero o puedo usar una referencia
    void join_game(uint8_t game_code, ServerSide::Client* client);

    ~Lobby();

    /*
     *  No queremos ni copiar ni mover el monitor
     */
    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    Lobby(Lobby&&) = delete;
    Lobby& operator=(Lobby&&) = delete;
};


#endif //WORMS2D_LOBBY_H
