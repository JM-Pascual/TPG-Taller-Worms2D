#include "broadcaster.h"

#include <algorithm>

#include "Player.h"

void BroadCaster::add_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue) {
    std::lock_guard<std::mutex> l(m);
    broadcast_map.insert({id, &state_queue});
}

void BroadCaster::broadcast(const std::list<std::shared_ptr<States>>& game_states) {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [id, client_game_state_queue]: broadcast_map) {
        try {
            for (const auto& gs: game_states) {
                client_game_state_queue->push(gs);
            }

        } catch (const ClosedQueue& e) {  // Se ignoran queues cerradas, luego se eliminan
            continue;
        }
    }
}

void BroadCaster::remove_closed_clients(uint8_t& ready_count,
                                        std::map<uint8_t, Player>& players_stats) {
    std::lock_guard<std::mutex> lock(m);

    for (auto it = broadcast_map.rbegin(); it != broadcast_map.rend();) {
        if (it->second->is_closed()) {
            uint8_t id = it->first;
            broadcast_map.erase(id);
            players_stats.erase(id);
            ready_count--;
        }

        if (broadcast_map.empty()) {
            return;
        }

        ++it;
    }
}

void BroadCaster::removePlayer(const uint8_t& player_id) {
    std::lock_guard<std::mutex> lock(m);
    broadcast_map.erase(player_id);
}
