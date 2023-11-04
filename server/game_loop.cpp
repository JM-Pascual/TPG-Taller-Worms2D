#include "game_loop.h"

#include <chrono>

#include <spdlog/spdlog.h>
#include <unistd.h>

#include "../common/GameState.h"

#include "player_action.h"
#include "sclient.h"

Queue<std::shared_ptr<PlayerAction>>& GameLoop::get_action_queue() { return this->action_queue; }

void GameLoop::add_client_queue(const uint8_t& id, Queue<std::shared_ptr<GameState>>& state_queue) {
    this->game.add_client_queue(id, state_queue);
}

void GameLoop::set_player_ready(const uint8_t id) {
    game.set_player_ready(id);
    if (not _is_alive && game.is_playing()) {
        this->start();
    }
}

const bool GameLoop::game_started_playing() { return game.is_playing(); }

void GameLoop::run() {
    while (game.is_playing()) {  // ToDo Aca se podria meter un bool que se cambia con un comando
                                 // exit
        std::chrono::time_point<std::chrono::system_clock> before =
                std::chrono::system_clock::now();

        std::shared_ptr<PlayerAction> c;
        if (action_queue.try_pop(c)) {
            c->execute(game);
        }

        game.broadcast_game_state();
        // dormir(tiempo del tick del sv - tiempo que tarde en llegar acá)

        game.remove_closed_clients();

        std::chrono::time_point<std::chrono::system_clock> after = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds =
                std::chrono::milliseconds(EST_TICK_TIME) - (after - before);

        std::this_thread::sleep_for(elapsed_seconds);
    }
}

GameLoop::~GameLoop() {}
