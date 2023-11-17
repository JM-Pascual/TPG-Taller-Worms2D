#include "broadcaster.h"

#include <algorithm>

#include <spdlog/spdlog.h>

#include "Player.h"
#include "battlefield.h"

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
                                        std::map<uint8_t, std::unique_ptr<Player>>& players_stats,
                                        Battlefield& battlefield) {
    std::lock_guard<std::mutex> lock(m);

    auto it = broadcast_map.cbegin();
    while (it != broadcast_map.cend()) {
        if (it->second->is_closed()) {
            uint8_t id = it->first;
            it = broadcast_map.erase(it);
            battlefield.destroy_body(players_stats.at(id)->body);
            players_stats.erase(id);
            ready_count--;
            continue;
        }

        ++it;
    }
}

void BroadCaster::removePlayer(const uint8_t& player_id) {
    std::lock_guard<std::mutex> lock(m);
    broadcast_map.erase(player_id);
}
