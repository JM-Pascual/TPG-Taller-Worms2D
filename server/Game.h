#ifndef GAME_H
#define GAME_H

#include <list>
#include <memory>
#include <mutex>

#include "../common/GameState.h"
#include "../common/const.h"
#include "../common/queue.h"

#include "Player.h"

#define TICK_RATE 60
#define EST_TICK_TIME 1000 / TICK_RATE

class Game {
private:
    std::mutex m;
    std::list<Queue<std::shared_ptr<GameState>>*> broadcast_list;
    Player player;

    [[nodiscard]] std::shared_ptr<GameState> get_game_state() const;

    void update_game_state();

public:
    Game() = default;

    void add_client_queue(Queue<std::shared_ptr<GameState>>& client_game_state);

    // Envia el DTO GameState a todos los clientes conectados
    void broadcast_game_state();

    void remove_closed_clients();

    bool is_playing();

    // temp protocol
    void player_start_moving(const MoveDir& direction);
    void player_stop_moving();
};


#endif  // GAME_H
