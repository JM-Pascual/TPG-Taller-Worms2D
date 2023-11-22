#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <list>
#include <map>
#include <memory>
#include <mutex>

#include "../common/queue.h"

#include "info_parser.h"

class States;
class Player;
class Battlefield;

class BroadCaster {
private:
    std::mutex m;
    /*
        Este mutex es necesario ya que mientras el juego este en estado "lobby", multiples hilos
       intentan acceder al mapa.
    */
    std::map<uint8_t, Queue<std::shared_ptr<States>>*> broadcast_map;
    InfoParser infoParser;

    void broadcast(const std::list<std::shared_ptr<States>>& game_states);

public:
    explicit BroadCaster(Game& game): infoParser(game) {}

    void add_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue);

    void broadcastLobby();

    void broadcastGame(uint8_t id_of_active_player);

    void remove_closed_clients(uint8_t& ready_count,
                               std::map<uint8_t, std::unique_ptr<Player>>& players);

    void removeLobbyPlayer(const uint8_t& player_id);

    void broadcast_turn(const uint8_t& player_turn, const bool& block_input = false);

    ~BroadCaster() = default;
};


#endif
