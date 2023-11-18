#ifndef GAME_H
#define GAME_H

#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include "../common/States.h"
#include "../common/const.h"
#include "../common/queue.h"
#include "box2d/box2d.h"

#include "Player.h"
#include "battlefield.h"
#include "broadcaster.h"
#include "game_loop.h"
#include "level_holder.h"

#define MAX_PLAYERS 4

class Projectile;

class Game {
private:
    std::mutex m;
    std::map<uint8_t, std::unique_ptr<Player>> players_stats;
    uint8_t ready_count;

    const std::string description;
    const std::string map_name;
    const uint8_t game_id;

    GameLoop gameloop;
    bool need_to_join_loop;

    Battlefield battlefield;
    BroadCaster broadcaster;
    // int16_t para poder iniciarlo en -1 y que se tome bien el proximo turno
    int16_t prev_player_turn_id;


    void build_game_state(std::list<std::shared_ptr<States>>& states_list);

    bool non_locking_is_playing();

    void notifyLobbyState();

public:
    Game(std::string desc, const std::string& map, const uint8_t& game_id,
         Queue<uint8_t>& erase_id_queue):
            ready_count(0),
            description(std::move(desc)),
            map_name(map),
            game_id(game_id),
            gameloop(*this, this->game_id, erase_id_queue),
            need_to_join_loop(false),
            prev_player_turn_id(-1) {}

    Queue<std::shared_ptr<PlayerAction>>& get_action_queue();

    void add_client_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue);

    // Envia el DTO States a todos los clientes conectados
    void broadcast_game_state();

    void remove_closed_clients();

    void removeLobbyPlayer(const uint8_t& player_id);

    bool isEmpty();

    bool is_playing();

    void set_player_ready(uint8_t id);


    const uint8_t broadcast_turn(const uint8_t& player_turn);

    const uint8_t players_alive();

    void step();
    void update_physics();
    void update_weapon();


    // temp protocol
    void player_start_moving(const Direction& direction, uint8_t id);
    void player_stop_moving(uint8_t id);
    void player_jump(const JumpDir& direction, uint8_t id);
    void player_start_aiming(const ADSAngleDir& direction, uint8_t id);
    void player_stop_aiming(const uint8_t id);
    void player_start_charging(const uint8_t id);
    void player_shoot(const uint8_t id);

    void remove_collided_projectiles();

    void remove_box2d_entities();
    void stop_all_players();

    std::shared_ptr<GameInfoL> getInfo();

    ~Game();
};


#endif  // GAME_H
