#ifndef GAME_H
#define GAME_H

#include <list>
#include <memory>
#include <mutex>

#include "../common/GameState.h"
#include "../common/const.h"
#include "../common/queue.h"

#include "Player.h"
#include "box2d/box2d.h"

#define TICK_RATE 60
#define EST_TICK_TIME 1000 / TICK_RATE
#define X_GRAVITY 0.0f
#define Y_GRAVITY (-10.0f)

class Game {
private:
    std::mutex m;
    std::list<Queue<std::shared_ptr<GameState>>*> broadcast_list;
    b2Vec2 gravity;
    std::unique_ptr<b2World> world;
    Player player;




    [[nodiscard]] std::shared_ptr<GameState> get_game_state() const;

    void create_battlefield();

public:
    Game();

    void add_client_queue(Queue<std::shared_ptr<GameState>>& client_game_state);

    // Envia el DTO GameState a todos los clientes conectados
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
