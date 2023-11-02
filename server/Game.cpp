#include "Game.h"

#include <spdlog/spdlog.h>

std::shared_ptr<GameState> Game::get_game_state() const {
    return std::make_shared<GameState>(player.position.x, player.position.y, player.velocity.x != 0,
                                       player.facing_right);
}

void Game::update_game_state() {
    player.position.x += player.velocity.x;
    player.position.y += player.velocity.y;
}


void Game::add_client_queue(Queue<std::shared_ptr<GameState>>& client_game_state) {
    std::lock_guard<std::mutex> lock(m);
    broadcast_list.push_back(&client_game_state);
}

void Game::broadcast_game_state() {
    update_game_state();
    std::shared_ptr<GameState> gs = get_game_state();

    std::lock_guard<std::mutex> lock(m);
    for (auto& client_game_state_queue: broadcast_list) {
        try {
            client_game_state_queue->push(gs);

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
    return (broadcast_list.size() > 0);
}

void Game::player_start_moving(const MoveDir& direction) {
    player.facing_right = (bool)direction;
    // ToDo Incremento temporal de la velocidad, cuando haya físicas hay que pulirlo
    player.velocity.x = 0.2 * (std::pow(-1, 1 - player.facing_right) / TICK_RATE) * 200;
}

void Game::player_stop_moving() { player.velocity.x = 0; }
