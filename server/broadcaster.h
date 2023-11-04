#ifndef BROADCASTER_H
#define BROADCASTER_H

#include <list>
#include <memory>
#include <mutex>

#include "../common/queue.h"

class GameState;

class BroadCaster {
private:
    std::mutex m;
    std::list<Queue<std::shared_ptr<GameState>>*> broadcast_list;

public:
    BroadCaster() = default;

    void add_queue(Queue<std::shared_ptr<GameState>>& state_queue);

    void broadcast(const std::list<std::shared_ptr<GameState>>& game_states);

    void remove_closed_clients(uint8_t& ready_count);

    ~BroadCaster() = default;
};


#endif
