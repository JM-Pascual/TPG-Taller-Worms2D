#include "Game.h"

#include <utility>

#include <spdlog/spdlog.h>

#include "game_loop.h"

void Game::build_game_state(std::list<std::shared_ptr<GameState>>& states_list) {
    std::lock_guard<std::mutex> l(m);

    states_list.push_back(std::make_shared<PlayerCount>(players_stats.size()));

    for (const auto& [id, player]: players_stats) {
        states_list.push_back(std::make_shared<PlayerState>(
                player.worm->GetPosition().x, player.worm->GetPosition().y,
                player.is_walking, player.is_jumping, player.is_backflipping, player.facing_right,
                player.aim_inclination_degrees));
    }

    states_list.push_back(std::make_shared<ProyectileCount>(battlefield.proyectile.size()));

    for (const auto& proyectile: battlefield.proyectile) {
        states_list.push_back(proyectile->get_proyectile_state());
    }
}

bool Game::non_locking_is_playing() {
    return (!players_stats.empty() && players_stats.size() == ready_count);
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
    update_weapon();

    std::list<std::shared_ptr<GameState>> state_list;
    build_game_state(state_list);

    broadcaster.broadcast(state_list);
}

void Game::remove_closed_clients() {
    broadcaster.remove_closed_clients(ready_count, players_stats);
}

bool Game::is_playing() {
    std::lock_guard<std::mutex> lock(m);
    return (!players_stats.empty() && players_stats.size() == ready_count);
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
    if (not gameloop.is_alive() && this->non_locking_is_playing()) {
        gameloop.start();
    }
}

void Game::player_start_moving(const Direction& direction, const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).is_walking = true;
    players_stats.at(id).facing_right = (bool)direction;
    players_stats.at(id).move();
}

void Game::player_stop_moving(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).is_walking = false;
    players_stats.at(id).stop();
}

void Game::player_jump(const JumpDir& direction, const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).jump(direction);
}

void Game::step() {
    battlefield.step();
}

void Game::update_physics() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [id, player]: players_stats) {
        player.check_jumping();
        if(!player.is_walking && !player.is_jumping && !player.is_backflipping){
            player.stop();
        }else if(player.is_walking) {
            player.move();
        }
    }
}

Game::~Game() {
    spdlog::get("server")->debug("Joineando gameloop");
    gameloop.join();
}

void Game::player_start_aiming(const ADSAngleDir& direction,const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).aiming = true;
    players_stats.at(id).aim_direction = direction;
}

void Game::player_stop_aiming(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).aiming = false;
}

void Game::update_weapon() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [id, player]: players_stats) {
        if(player.aiming){
            player.change_aim_direction();
        }
        if(player.charging_shoot){
            player.change_fire_power();
        }
    }
}

void Game::player_start_charging(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).charging_shoot = true;
}

void Game::player_shoot(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).aiming = false;
    players_stats.at(id).charging_shoot = false;

    players_stats.at(id).shoot(battlefield);

    players_stats.at(id).weapon_power = 0;
}

