#ifndef GAME_H
#define GAME_H

#include <list>
#include <map>
#include <memory>
#include <mutex>

#include "../common/GameState.h"
#include "../common/const.h"
#include "../common/queue.h"
#include "box2d/box2d.h"

#include "Player.h"
#include "battlefield.h"
#include "broadcaster.h"
#include "game_loop.h"


class Game {
private:
    std::mutex m;
    std::map<uint8_t, Player> players_stats;

    BroadCaster broadcaster;
    Battlefield battlefield;
    uint8_t ready_count;
    const uint8_t game_id;
    GameLoop gameloop;

    void build_game_state(std::list<std::shared_ptr<GameState>>& states_list);

    bool non_locking_is_playing();

public:
    Game(const uint8_t game_id, Queue<uint8_t>& erase_id_queue):
            ready_count(0), game_id(game_id), gameloop(*this, this->game_id, erase_id_queue) {}

    Queue<std::shared_ptr<PlayerAction>>& get_action_queue();

    void add_client_queue(const uint8_t& id, Queue<std::shared_ptr<GameState>>& state_queue);

    // Envia el DTO GameState a todos los clientes conectados
    void broadcast_game_state();

    void remove_closed_clients();

    bool is_playing();

    void set_player_ready(uint8_t id);

    // temp protocol
    void player_start_moving(const Direction& direction, uint8_t id);
    void player_stop_moving(uint8_t id);
    void player_jump(const JumpDir& direction, uint8_t id);
    void player_position(const uint8_t id);

    void step();
    void update_physics();

    ~Game();
};


#endif  // GAME_H
