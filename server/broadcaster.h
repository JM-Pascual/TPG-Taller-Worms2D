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
    BroadCaster(std::mutex& m_game, std::map<uint8_t, std::unique_ptr<Player>>& players,
                std::map<uint8_t, std::shared_ptr<Projectile>>& projectiles):
            infoParser(m_game, players, projectiles) {}

    void add_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue);

    void broadcastLobby();

    void broadcastGame();

    void remove_closed_clients(uint8_t& ready_count,
                               std::map<uint8_t, std::unique_ptr<Player>>& players_stats,
                               Battlefield& battlefield);

    void removeLobbyPlayer(const uint8_t& player_id);

    void broadcast_turn(const uint8_t& player_turn);

    ~BroadCaster() = default;
};


#endif
