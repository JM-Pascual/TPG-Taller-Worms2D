#include "Game.h"

#include <spdlog/spdlog.h>

Game::Game():player(battlefield){
}

void Game::get_game_state(std::list<std::shared_ptr<GameState>>& p) const {
    p.clear();
    for (const auto& [id, player]: players_stats) {
        p.push_back(std::make_shared<PlayerState>(player.worm->GetPosition().x, player.worm->GetPosition().y, player.worm->GetLinearVelocity().x != 0,
                                                  player.facing_right));
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
    update_physics();
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
    return (broadcast_list.size() > 0 ? broadcast_list.size() == ready_count : false);
}

void Game::set_player_ready(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    if (players_stats.count(id) == 1) {
        players_stats[id].set_ready();
        ready_count += std::pow(-1, 1 - players_stats[id].ready);
    }
}

void Game::player_start_moving(const Direction& direction, const uint8_t id) {
    players_stats[id].facing_right = (bool)direction;
    players_stats[id].is_moving = true;
    // ToDo Incremento temporal de la velocidad, cuando haya físicas hay que pulirlo

    b2Vec2 vel = players_stats[id].worm->GetLinearVelocity();
    vel.x = 0.2f* (std::pow(-1, 1 - players_stats[id].facing_right) / TICK_RATE)* 400;
    players_stats[id].worm->SetLinearVelocity(vel); // Esto tengo que ver si esta bien, se ve cuando lo corra
}

void Game::player_stop_moving(const uint8_t id) {
    players_stats[id].is_moving = false;
    b2Vec2 vel = players_stats[id].worm->GetLinearVelocity();
    vel.x = 0;
    players_stats[id].worm->SetLinearVelocity(vel);
}

void Game::step() {
    battlefield.step();
}

void Game::update_physics() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [id, player]: players_stats) {
        b2Vec2 vel = player.worm->GetLinearVelocity();
        vel.x = player.is_moving * (0.2f* (std::pow(-1, 1 - player.facing_right) / TICK_RATE)* 400); // Agregar comentario
        player.worm->SetLinearVelocity(vel);
    }
}

