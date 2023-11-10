#include "Game.h"

#include <algorithm>
#include <utility>

#include <spdlog/spdlog.h>

#include "game_loop.h"

void Game::get_game_state(std::list<std::shared_ptr<States>>& states_list) {
    std::lock_guard<std::mutex> l(m);

    states_list.push_back(std::make_shared<PlayerCountG>(players_stats.size()));

    for (const auto& [id, player]: players_stats) {
        states_list.push_back(std::make_shared<PlayerStateG>(
                player.worm->GetPosition().x, player.worm->GetPosition().y,
                player.worm->GetLinearVelocity().x != 0, player.facing_right));
    }
}

bool Game::not_lock_is_playing() {
    return (players_stats.size() > 0 ? players_stats.size() == ready_count : false);
}

void Game::notifyLobbyState() {
    std::list<std::shared_ptr<States>> lobby_state_list;
    lobby_state_list.push_back(std::make_shared<PlayerCountL>(players_stats.size()));

    // for (auto& player: players_stats) {
    //     lobby_state_list.push_back(
    //             std::make_shared<PlayerStateL>(player.second.ready, player.first));
    // }

    std::transform(players_stats.begin(), players_stats.end(), std::back_inserter(lobby_state_list),
                   [&](std::pair<uint8_t, Player> player) {
                       return std::make_shared<PlayerStateL>(player.second.ready, player.first);
                   });

    broadcaster.broadcast(lobby_state_list);
}

Queue<std::shared_ptr<PlayerAction>>& Game::get_action_queue() {
    return this->gameloop.get_action_queue();
}

void Game::add_client_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue) {
    remove_closed_clients();

    std::lock_guard<std::mutex> lock(m);

    if (not_lock_is_playing()) {
        state_queue.push(std::make_shared<GameNotJoinable>());
        return;
    }

    if (players_stats.size() >= MAX_PLAYERS) {
        state_queue.push(std::make_shared<GameNotJoinable>());
        return;
    }

    broadcaster.add_queue(id, state_queue);
    players_stats.insert(std::make_pair(id, Player(battlefield)));
    notifyLobbyState();
}

void Game::broadcast_game_state() {
    update_physics();

    std::list<std::shared_ptr<States>> state_list;
    get_game_state(state_list);

    broadcaster.broadcast(state_list);
}

void Game::remove_closed_clients() {
    std::lock_guard<std::mutex> lock(m);
    broadcaster.remove_closed_clients(ready_count, players_stats);
}

void Game::removePlayer(const uint8_t& player_id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.erase(player_id);
    broadcaster.removePlayer(player_id);
}

bool Game::isEmpty() { return players_stats.size() == 0; }

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

    notifyLobbyState();

    // Inicio el gl si estan todos listos y no esta iniciado ya
    if (not gameloop.is_alive() && this->not_lock_is_playing()) {
        gameloop.start();
        need_to_join_loop = true;
    }
}

void Game::player_start_moving(const Direction& direction, const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).facing_right = (bool)direction;
    players_stats.at(id).is_moving = true;

    b2Vec2 vel = players_stats.at(id).worm->GetLinearVelocity();
    vel.x = 0.2f * (std::pow(-1, 1 - players_stats.at(id).facing_right) / TICK_RATE) * 400;
    players_stats.at(id).worm->SetLinearVelocity(
            vel);  // Esto tengo que ver si esta bien, se ve cuando lo corra
}

void Game::player_stop_moving(const uint8_t id) {
    std::lock_guard<std::mutex> lock(m);
    players_stats.at(id).is_moving = false;
    b2Vec2 vel = players_stats.at(id).worm->GetLinearVelocity();
    vel.x = 0;
    players_stats.at(id).worm->SetLinearVelocity(vel);
}

void Game::step() { battlefield.step(); }

void Game::update_physics() {
    std::lock_guard<std::mutex> lock(m);
    for (auto& [id, player]: players_stats) {
        b2Vec2 vel = player.worm->GetLinearVelocity();
        vel.x = player.is_moving *
                (0.2f * (std::pow(-1, 1 - player.facing_right) / TICK_RATE) * 400);
        // 0 si el jugador no se mueve, el resto de la ecuacion si se esta moviendo
        player.worm->SetLinearVelocity(vel);
    }
}

std::shared_ptr<GameInfoL> Game::getInfo() {
    std::lock_guard<std::mutex> lock(m);
    return std::make_shared<GameInfoL>(description, map_name, players_stats.size(), game_id);
}

Game::~Game() {
    spdlog::get("server")->debug("Joineando gameloop");
    if (need_to_join_loop) {
        gameloop.join();
    }
}
