#include "Game.h"

#include <spdlog/spdlog.h>

std::shared_ptr<GameState> Game::get_game_state() const {
    return std::make_shared<GameState>(player.x, player.y, player.is_walking, player.facing_right);
}

void Game::update_game_state() {
    spdlog::get("server")->info("is_wk: {:d}", player.is_walking);
    if (player.is_walking) {
        player.x += (2 * player.facing_right - 1);
        spdlog::get("server")->info("x: {:f}", player.x);
    }
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
        client_game_state_queue->push(gs);
    }
}

void Game::player_start_moving() { player.is_walking = true; }
void Game::player_stop_moving() { player.is_walking = false; }
