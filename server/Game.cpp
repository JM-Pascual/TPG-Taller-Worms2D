#include "Game.h"

GameState Game::get_game_state() const {
    return (GameState{player.x, player.y, player.is_walking, player.direction});
}

void Game::add_client_queue(Queue<GameState>& client_game_state) {
    std::lock_guard<std::mutex> lock(m);
    broadcast_list.push_back(&client_game_state);
}

void Game::broadcast_game_state() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& client_game_state_queue: broadcast_list) {
        client_game_state_queue->push(get_game_state());
    }
}

void Game::player_start_moving() {
    player.is_walking = true;
}
void Game::player_stop_moving() {
    player.is_walking = false;
}
