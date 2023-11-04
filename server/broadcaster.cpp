#include "broadcaster.h"

#include <algorithm>

void BroadCaster::add_queue(Queue<std::shared_ptr<GameState>>& state_queue) {
    std::lock_guard<std::mutex> l(m);
    broadcast_list.push_back(&state_queue);
}

void BroadCaster::broadcast(const std::list<std::shared_ptr<GameState>>& game_states) {
    std::lock_guard<std::mutex> lock(m);
    for (auto& client_game_state_queue: broadcast_list) {
        try {
            for (const auto& gs: game_states) {
                client_game_state_queue->push(gs);
            }

        } catch (const ClosedQueue& e) {  // Se ignoran queues cerradas, luego se eliminan
            continue;
        }
    }
}

void BroadCaster::remove_closed_clients(uint8_t& ready_count) {
    std::lock_guard<std::mutex> lock(m);

    auto before = broadcast_list.size();
    broadcast_list.erase(std::remove_if(broadcast_list.begin(), broadcast_list.end(),
                                        [&](Queue<std::shared_ptr<GameState>>* q) {
                                            if (q->is_closed()) {
                                                return true;
                                            }
                                            return false;
                                        }),
                         broadcast_list.end());

    ready_count -= (before - broadcast_list.size());
}
