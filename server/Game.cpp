#include "Game.h"

#include <utility>

#include <spdlog/spdlog.h>

#include "game_loop.h"

void Game::get_game_state(std::list<std::shared_ptr<GameState>>& states_list) {
    std::lock_guard<std::mutex> l(m);

    states_list.push_back(std::make_shared<PlayerCount>(players_stats.size()));

    for (const auto& [id, player]: players_stats) {
        states_list.push_back(std::make_shared<PlayerState>(
                player.worm->GetPosition().x, player.worm->GetPosition().y,
                player.worm->GetLinearVelocity().x != 0, player.facing_right));
    }
}

bool Game::not_lock_is_playing() {
    return (players_stats.size() > 0 ? players_stats.size() == ready_count : false);
}

Queue<std::shared_ptr<PlayerAction>>& Game::get_action_queue() {
    return this->gameloop.get_action_queue();
}

void Game::add_client_queue(const uint8_t& id, Queue<std::shared_ptr<GameState>>& state_queue) {
    std::lock_guard<std::mutex> lock(m);

    broadcaster.add_queue(id, state_queue);
    players_stats.insert(std::make_pair(id, Player(battlefield)));
}

void Game::broadcast_game_state() {
    update_physics();

    std::list<std::shared_ptr<GameState>> state_list;
    get_game_state(state_list);

    broadcaster.broadcast(state_list);
}

void Game::remove_closed_clients() {
    broadcaster.remove_closed_clients(ready_count, players_stats);
}

bool Game::is_playing() {
    std::lock_guard<std::mutex> lock(m);
    return (players_stats.size() > 0 ? players_stats.size() == ready_count : false);
}

void Game::set_player_ready(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    // Esta unido al game el player[id]?
    if (players_stats.count(id) == 1) {
        players_stats.at(id).set_ready();
        // Resta si el player dio unready, inc si dio ready
        ready_count += std::pow(-1, 1 - players_stats.at(id).ready);
    }

    // Inicio el gl si estan todos listos y no esta iniciado ya
    if (not gameloop.is_alive() && this->not_lock_is_playing()) {
        gameloop.start();
    }
}

void Game::player_start_moving(const Direction& direction, const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).is_moving = true;
    players_stats.at(id).facing_right = (bool)direction;
    players_stats.at(id).move();
}

void Game::player_stop_moving(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).is_moving = false;
    players_stats.at(id).stop();
}

void Game::player_jump(const JumpDir& direction, const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).is_jumping = true;
    players_stats.at(id).jump(direction);
}

void Game::step() {
    battlefield.step();
}

void Game::update_physics() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [id, player]: players_stats) {
        player.check_jumping();
        if(!player.is_moving && !player.is_jumping){
            player.stop();
        }else if(player.is_moving) {
            player.move();
        }else if(player.is_jumping){
            player.keep_jumping();
        }
    }
}

Game::~Game() {
    spdlog::get("server")->debug("Joineando gameloop");
    gameloop.join();
}

void Game::player_position(const uint8_t id) {
    std::cout << players_stats.at(id).worm->GetPosition().x << " " << players_stats.at(id).worm->GetPosition().y << std::endl;
}


