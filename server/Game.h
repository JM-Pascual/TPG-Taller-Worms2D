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
#include "worm_handler.h"

#define MAX_PLAYERS 4
#define WORMS_QUANTITY 2

class Projectile;

class Game {
private:
    Battlefield battlefield;
    std::mutex m;
    /*
        Este mutex es necesario ya que mientras el juego este en estado "lobby", multiples hilos
       intentan acceder al mapa.
    */
    std::map<uint8_t, std::unique_ptr<Player>> players_stats;
    uint8_t ready_count;

    uint8_t worm_counter;

    const std::string description;
    const std::string map_name;
    const uint8_t game_id;

    WormHandler worm_handler;
    BroadCaster broadcaster;

    GameLoop gameloop;
    bool need_to_join_loop;

    void notifyLobbyState();

    bool non_locking_is_playing();

    void spawnWorms();

public:
    Game(std::string desc, const std::string& map, const uint8_t& game_id,
         Queue<uint8_t>& erase_id_queue):
            ready_count(0),
            worm_counter(0),
            description(std::move(desc)),
            map_name(map),
            game_id(game_id),
            worm_handler(players_stats),
            broadcaster(m, players_stats, battlefield.getProjectiles()),
            gameloop(*this, this->game_id, erase_id_queue),
            need_to_join_loop(false) {}

    Queue<std::shared_ptr<PlayerAction>>& get_action_queue();

    std::shared_ptr<GameInfoL> getInfo();

    void add_client_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue);

    void removeLobbyPlayer(const uint8_t& player_id);

    bool isEmpty();

    bool is_playing();

    void set_player_ready(uint8_t id);

    ~Game();

    friend class GameLoop;
};


#endif  // GAME_H
