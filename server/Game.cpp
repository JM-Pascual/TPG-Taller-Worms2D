#include "Game.h"

#include <spdlog/spdlog.h>

void Game::get_game_state(std::list<std::shared_ptr<GameState>>& p) const {
    p.clear();
    for (const auto& [id, player]: players_stats) {
        p.push_back(std::make_shared<PlayerState>(player.position.x, player.position.y,
                                                  player.velocity.x != 0, player.facing_right));
    }
}

void Game::update_game_state() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [id, player]: players_stats) {
        player.position.x += player.velocity.x;
        player.position.y += player.velocity.y;
    }
}


void Game::add_client_queue(const uint8_t& id, Queue<std::shared_ptr<GameState>>& state_queue) {
    std::lock_guard<std::mutex> lock(m);

    broadcast_list.push_back(&state_queue);
    players_stats[id] = Player();
}

void Game::broadcast_game_state() {
    update_game_state();
    std::list<std::shared_ptr<GameState>> state_list;
    get_game_state(state_list);

    std::lock_guard<std::mutex> lock(m);
    for (auto& client_game_state_queue: broadcast_list) {
        try {
            if (state_list.size() > 0)
                client_game_state_queue->push(std::make_shared<PlayerCount>(broadcast_list.size()));

            for (const auto& gs: state_list) {
                client_game_state_queue->push(gs);
            }

        } catch (const ClosedQueue& e) {
            continue;
        }
    }
}

void Game::remove_closed_clients() {
    std::lock_guard<std::mutex> lock(m);
    broadcast_list.erase(
            std::remove_if(broadcast_list.begin(), broadcast_list.end(),
                           [](Queue<std::shared_ptr<GameState>>* q) { return q->is_closed(); }),
            broadcast_list.end());
}

bool Game::is_playing() {
    std::lock_guard<std::mutex> lock(m);
    return (broadcast_list.size() == ready_count);
}

void Game::set_player_ready(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats[id].set_ready();
    ready_count += std::pow(-1, 1 - players_stats[id].ready);
}

void Game::player_start_moving(const Direction& direction, const uint8_t id) {
    players_stats[id].facing_right = (bool)direction;
    // ToDo Incremento temporal de la velocidad, cuando haya físicas hay que pulirlo
    players_stats[id].velocity.x =
            0.2 * (std::pow(-1, 1 - players_stats[id].facing_right) / TICK_RATE) * 200;
}

void Game::player_stop_moving(const uint8_t id) { players_stats[id].velocity.x = 0; }
