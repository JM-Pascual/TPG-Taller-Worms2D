#include "game_loop.h"

#include <chrono>

#include <spdlog/spdlog.h>

#include "Game.h"
#include "player_action.h"
#include "sclient.h"

Queue<std::shared_ptr<PlayerAction>>& GameLoop::get_action_queue() { return this->action_queue; }

void GameLoop::run() {
    while (game.is_playing()) {
        std::chrono::time_point<std::chrono::system_clock> before =
                std::chrono::system_clock::now();

        std::shared_ptr<PlayerAction> c;
        if (action_queue.try_pop(c)) {
            c->execute(game);
        }
        game.step();

        game.broadcast_game_state();
        // dormir(tiempo del tick del sv - tiempo que tarde en llegar acá)

        game.remove_closed_clients();

        std::chrono::time_point<std::chrono::system_clock> after = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds =
                std::chrono::milliseconds(EST_TICK_TIME) - (after - before);

        std::this_thread::sleep_for(elapsed_seconds);
    }
}
