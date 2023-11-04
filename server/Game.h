#ifndef GAME_H
#define GAME_H

#include <list>
#include <memory>
#include <mutex>

#include "../common/WormGameState.h"
#include "../common/BattlefieldGameState.h"
#include "../common/const.h"
#include "../common/queue.h"

#include "Player.h"
#include "battlefield.h"
#include "box2d/box2d.h"

#define TICK_RATE 30
#define EST_TICK_TIME 1000 / TICK_RATE

class Game {
private:
    std::mutex m;
    std::list<Queue<std::shared_ptr<WormGameState>>*> broadcast_list;
    Battlefield battlefield;
    Player player;


    [[nodiscard]] std::shared_ptr<WormGameState> get_game_state() const;
    //[[nodiscard]] std::shared_ptr<BattlefieldGameState> get_battlefield() const;

public:
    Game();

    void add_client_queue(Queue<std::shared_ptr<WormGameState>>& client_game_state);

    // Envia el DTO WormGameState a todos los clientes conectados
    void broadcast_game_state();

    void remove_closed_clients();

    bool is_playing();

    // temp protocol
    void player_start_moving(const MoveDir& direction);
    void player_stop_moving();

    void step();
    void update_physics();

};


#endif  // GAME_H
