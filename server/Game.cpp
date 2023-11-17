#include "Game.h"

#include <algorithm>
#include <utility>

#include <spdlog/spdlog.h>

#include "game_loop.h"
#include "proyectile.h"

void Game::build_game_state(std::list<std::shared_ptr<States>>& states_list) {
    std::lock_guard<std::mutex> l(m);

    states_list.push_back(std::make_shared<PlayerCountG>(players_stats.size()));

    for (auto& player: players_stats) {
        // cppcheck-suppress useStlAlgorithm
        states_list.push_back(std::make_shared<PlayerStateG>(
                player.first,
                player.second->body->GetPosition().x, player.second->body->GetPosition().y,
                player.second->is_walking, player.second->is_jumping,
                player.second->is_backflipping, player.second->facing_right,
                (player.second->contact_points >= 1), player.second->aim_inclination_degrees,
                player.second->charging_shoot, player.second->life));
    }

    states_list.push_back(std::make_shared<ProjectileCountG>(projectiles.size()));

    std::transform(projectiles.begin(), projectiles.end(), std::back_inserter(states_list),
                   [](auto& projectile) { return projectile.second->get_proyectile_state(
                                                  projectile.first); });
}

bool Game::non_locking_is_playing() {
    return (!players_stats.empty() && players_stats.size() == ready_count);
}

void Game::notifyLobbyState() {
    std::list<std::shared_ptr<States>> lobby_state_list;

    lobby_state_list.push_back(std::make_shared<PlayerCountL>(players_stats.size()));

    for (auto& player: players_stats) {
        // cppcheck-suppress useStlAlgorithm
        lobby_state_list.push_back(
                std::make_shared<PlayerStateL>(player.second->ready, player.first));
    }

    broadcaster.broadcast(lobby_state_list);
}

Queue<std::shared_ptr<PlayerAction>>& Game::get_action_queue() {
    return this->gameloop.get_action_queue();
}

void Game::add_client_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue) {
    remove_closed_clients();

    std::lock_guard<std::mutex> lock(m);

    if (non_locking_is_playing()) {
        state_queue.push(std::make_shared<GameNotJoinable>());
        return;
    }

    if (players_stats.size() >= MAX_PLAYERS) {
        state_queue.push(std::make_shared<GameNotJoinable>());
        return;
    }

    broadcaster.add_queue(id, state_queue);
    players_stats.insert(std::make_pair(id, std::make_unique<Player>(battlefield)));
    notifyLobbyState();
}

void Game::broadcast_game_state() {
    update_physics();
    update_weapon();

    std::list<std::shared_ptr<States>> state_list;
    build_game_state(state_list);

    broadcaster.broadcast(state_list);
}

void Game::remove_closed_clients() {
    std::lock_guard<std::mutex> lock(m);
    broadcaster.remove_closed_clients(ready_count, players_stats);
}

void Game::removePlayer(const uint8_t& player_id) {
    std::lock_guard<std::mutex> lock(m);

    if (players_stats.count(player_id) != 1) {
        return;
    }

    if (players_stats.at(player_id)->ready) {
        ready_count--;
    }
    players_stats.erase(player_id);
    broadcaster.removePlayer(player_id);

    notifyLobbyState();
}

bool Game::isEmpty() { return players_stats.empty(); }

bool Game::is_playing() {
    std::lock_guard<std::mutex> lock(m);
    return (!players_stats.empty() && players_stats.size() == ready_count);
}

void Game::set_player_ready(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    // Esta unido al game el player[id]?
    if (players_stats.count(id) == 1) {
        players_stats.at(id)->set_ready();
        // Resta si el player dio unready, inc si dio ready
        ready_count += std::pow(-1, 1 - players_stats.at(id)->ready);
    }

    notifyLobbyState();

    // Inicio el gl si estan todos listos y no esta iniciado ya
    if (not gameloop.is_alive() && this->non_locking_is_playing()) {
        gameloop.start();
        need_to_join_loop = true;
    }
}

void Game::step() {
    battlefield.clean_dead_entities();
    battlefield.step();
}

std::shared_ptr<GameInfoL> Game::getInfo() {
    std::lock_guard<std::mutex> lock(m);
    return std::make_shared<GameInfoL>(description, map_name, players_stats.size(), game_id);
}

// -------------- Projectiles Actions -------------------

void Game::add_projectile(std::shared_ptr<Projectile> proyectile) {
    // std::lock_guard<std::mutex> lock(m);
    projectiles.insert({projectile_count, proyectile});
    projectile_count++;
}

void Game::remove_collided_projectiles() {
    //std::lock_guard<std::mutex> lock(m);
    for (auto it = projectiles.rbegin(); it != projectiles.rend();) {
        if (it->second->is_dead()) {
            uint8_t id = it->first;
            projectiles.erase(id);
            players_stats.erase(id);
            ready_count--;
        }

        if (projectiles.empty()) {
            return;
        }

        ++it;
    }
}

// -------------- Player Actions -------------------

void Game::player_start_moving(const Direction& direction, const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id)->is_walking = true;
    players_stats.at(id)->facing_right = (bool)direction;
    players_stats.at(id)->move();
}

void Game::player_stop_moving(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id)->is_walking = false;
    players_stats.at(id)->stop();
}

void Game::player_jump(const JumpDir& direction, const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id)->jump(direction);
}

void Game::player_start_aiming(const ADSAngleDir& direction, const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id)->aiming = true;
    players_stats.at(id)->aim_direction = direction;
}

void Game::player_stop_aiming(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id)->aiming = false;
}

void Game::player_start_charging(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id)->charging_shoot = true;
}

void Game::player_shoot(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id)->aiming = false;
    players_stats.at(id)->charging_shoot = false;

    players_stats.at(id)->shoot(*this);

    players_stats.at(id)->weapon_power = 0;
}

// -------------- Update States -------------------

void Game::update_weapon() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [id, player]: players_stats) {
        if (player->aiming) {
            player->change_aim_direction();
        }
        if (player->charging_shoot) {
            player->change_fire_power();
        }
    }
}

void Game::update_physics() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [id, player]: players_stats) {
        player->check_jumping();
        if (!player->is_walking && !player->is_jumping && !player->is_backflipping) {
            player->stop();
        } else if (player->is_walking) {
            player->move();
        }
    }
}


Game::~Game() {
    spdlog::get("server")->debug("Joineando gameloop");
    if (need_to_join_loop) {
        gameloop.join();
    }
}

void Game::remove_box2d_entities() { battlefield.destroy_dead_entities(); }
