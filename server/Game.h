#ifndef GAME_H
#define GAME_H

#include <list>
#include <map>
#include <memory>
#include <mutex>

#include "../common/GameState.h"
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
    std::list<Queue<std::shared_ptr<GameState>>*> broadcast_list;
    std::map<uint8_t, Player> players_stats;
    uint8_t ready_count;
    Battlefield battlefield;

    void get_game_state(std::list<std::shared_ptr<GameState>>& p) const;

    //void update_game_state();

public:
    Game(): ready_count(0){}

    void add_client_queue(const uint8_t& id, Queue<std::shared_ptr<GameState>>& state_queue);

    // Envia el DTO GameState a todos los clientes conectados
    void broadcast_game_state();

    void remove_closed_clients();

    bool is_playing();

    void set_player_ready(uint8_t id);

    // temp protocol
    void player_start_moving(const Direction& direction, uint8_t id);
    void player_stop_moving(uint8_t id);

    void step();
    void update_physics();
};


#endif  // GAME_H
