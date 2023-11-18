#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <list>
#include <map>
#include <memory>
#include <mutex>

#include "../common/queue.h"

class States;
class Player;
class Battlefield;

class BroadCaster {
private:
    std::mutex m;
    std::map<uint8_t, Queue<std::shared_ptr<States>>*> broadcast_map;

public:
    BroadCaster() = default;

    void add_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue);

    void broadcast(const std::list<std::shared_ptr<States>>& game_states);

    void remove_closed_clients(uint8_t& ready_count,
                               std::map<uint8_t, std::unique_ptr<Player>>& players_stats,
                               Battlefield& battlefield);

    void removeLobbyPlayer(const uint8_t& player_id);

    void broadcast_turn(const uint8_t& player_turn);

    ~BroadCaster() = default;
};


#endif
