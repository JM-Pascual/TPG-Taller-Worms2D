#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <list>
#include <map>
#include <memory>
#include <mutex>

#include "../common/queue.h"

class GameState;
class Player;

class BroadCaster {
private:
    std::mutex m;
    std::map<uint8_t, Queue<std::shared_ptr<GameState>>*> broadcast_map;

public:
    BroadCaster() = default;

    void add_queue(const uint8_t& id, Queue<std::shared_ptr<GameState>>& state_queue);

    void broadcast(const std::list<std::shared_ptr<GameState>>& game_states);

    void remove_closed_clients(uint8_t& ready_count, std::map<uint8_t, Player>& players_stats);

    ~BroadCaster() = default;
};


#endif
