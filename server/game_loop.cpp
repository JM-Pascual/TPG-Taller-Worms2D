#include "game_loop.h"

#include <chrono>
#include <utility>

#include <spdlog/spdlog.h>

#include "Game.h"
#include "player_action.h"
#include "sclient.h"
#include "turn_handler.h"

Queue<std::shared_ptr<PlayerAction>>& GameLoop::get_action_queue() { return this->action_queue; }

void GameLoop::run() {
    std::chrono::duration<float> elapsed_seconds = std::chrono::duration<float>(0);
    TurnHandler turn;
    uint8_t turn_id;
    std::pair<uint8_t, bool> turn_update;

    while (game.is_playing()) {
        std::chrono::time_point<std::chrono::steady_clock> before =
                std::chrono::steady_clock::now();

        turn_update = turn.update(game.players_alive(), elapsed_seconds);

        if (turn_update.second) {  // Si resetea el timer
            game.stop_all_players();
            turn_id = game.broadcast_turn(turn_update.first);
        }


        std::shared_ptr<PlayerAction> c;
        if (action_queue.try_pop(c)) {
            c->execute(game, turn_id);
        }

        game.step();

        game.broadcast_game_state();
        // dormir(tiempo del tick del sv - tiempo que tarde en llegar acá)

        game.remove_closed_clients();

        std::chrono::time_point<std::chrono::steady_clock> after = std::chrono::steady_clock::now();

        elapsed_seconds = std::chrono::milliseconds(EST_TICK_TIME) - (after - before);

        std::this_thread::sleep_for(elapsed_seconds);
    }

    erase_id_queue.push(this->game_id);
}
