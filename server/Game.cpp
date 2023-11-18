#include "Game.h"

#include <algorithm>
#include <numeric>
#include <utility>

#include <spdlog/spdlog.h>

#include "game_loop.h"
#include "proyectile.h"


bool Game::non_locking_is_playing() {
    return (!players_stats.empty() && players_stats.size() == ready_count);
}

void Game::notifyLobbyState() { broadcaster.broadcastLobby(); }

Queue<std::shared_ptr<PlayerAction>>& Game::get_action_queue() {
    return this->gameloop.get_action_queue();
}

void Game::add_client_queue(const uint8_t& id, Queue<std::shared_ptr<States>>& state_queue) {
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

void Game::removeLobbyPlayer(const uint8_t& player_id) {
    std::lock_guard<std::mutex> lock(m);

    if (players_stats.count(player_id) != 1) {
        return;
    }

    if (players_stats.at(player_id)->ready) {
        ready_count--;
    }
    players_stats.erase(player_id);
    broadcaster.removeLobbyPlayer(player_id);

    notifyLobbyState();
}

bool Game::isEmpty() {
    std::lock_guard<std::mutex> lock(m);
    return players_stats.empty();
}

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
