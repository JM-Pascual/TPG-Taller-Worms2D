#ifndef GAME_H
#define GAME_H

#include <list>
#include <mutex>
#include <memory>

#include "../common/GameState.h"
#include "../common/const.h"
#include "../common/queue.h"

#include "Player.h"


class Game {
private:
    std::mutex m;
    std::list<Queue<GameState>*> broadcast_list;
    Player player;

    [[nodiscard]] GameState get_game_state() const;
public:

    Game() = default;

    void add_client_queue(Queue<GameState>& client_game_state);
    //Envia el DTO GameState a todos los clientes conectados
    void broadcast_game_state();

    //temp protocol
    void player_start_moving();
    void player_stop_moving();
};


#endif  //GAME_H
