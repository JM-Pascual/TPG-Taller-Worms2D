#ifndef GAME_H
#define GAME_H

#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "../common/States.h"
#include "../common/const.h"
#include "../common/queue.h"
#include "box2d/box2d.h"

#include "Player.h"
#include "battlefield.h"
#include "broadcaster.h"
#include "game_loop.h"

#define MAX_PLAYERS 4

class Game {
private:
    std::mutex m;
    std::map<uint8_t, Player> players_stats;
    BroadCaster broadcaster;
    Battlefield battlefield;
    uint8_t ready_count;
    const std::string description;
    const std::string map_name;
    const uint8_t game_id;
    GameLoop gameloop;
    bool need_to_join_loop;

    void build_game_state(std::list<std::shared_ptr<States>>& states_list);

    bool non_locking_is_playing();

    void notifyLobbyState();

public:
    Game(const std::string& desc, const std::string& map, const uint8_t& game_id,
         Queue<uint8_t>& erase_id_queue):
            ready_count(0),
            description(desc),
            map_name(map),
            game_id(game_id),
            gameloop(*this, this->game_id, erase_id_queue),
            need_to_join_loop(false) {}

    Queue<std::shared_ptr<PlayerAction>>& get_action_queue();

    void add_client_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue);

    // Envia el DTO States a todos los clientes conectados
    void broadcast_game_state();

    void remove_closed_clients();

    void removePlayer(const uint8_t& player_id);

    bool isEmpty();

    bool is_playing();

    void set_player_ready(uint8_t id);

    const uint8_t broadcast_turn(const uint8_t& player_turn);

    const uint8_t players_alive();

    // temp protocol
    void player_start_moving(const Direction& direction, uint8_t id);
    void player_stop_moving(uint8_t id);
    void player_jump(const JumpDir& direction, uint8_t id);

    void step();
    void update_physics();
    void update_weapon();


    void player_start_aiming(const ADSAngleDir& direction, uint8_t id);
    void player_stop_aiming(const uint8_t id);

    void player_start_charging(const uint8_t id);
    void player_shoot(const uint8_t id);

    void stop_all_players();

    std::shared_ptr<GameInfoL> getInfo();

    ~Game();
};


#endif  // GAME_H
