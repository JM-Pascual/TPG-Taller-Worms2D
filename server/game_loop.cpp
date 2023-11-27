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
    TurnHandler turn_handler(game.players, game.broadcaster, game.worm_handler, game.battlefield);

    while (game.is_playing()) {
        std::chrono::time_point<std::chrono::steady_clock> before =
                std::chrono::steady_clock::now();

        ActualTurn turn_id = turn_handler.updateTurn(elapsed_seconds);

        std::shared_ptr<PlayerAction> c;
        if (action_queue.try_pop(c)) {
            c->execute(game.worm_handler, turn_id.player_id, turn_id.worm_index, turn_handler);
        }


        /*
         * Step -> Hago el step y marco como !alive las entidades físicas relacionadas
         * Hago el broad_cast para comunicar el estado a de todas las entidaddes del juego
         * Elimino las entidades de box2d
         * Elimino las entidades físicas relacionadas, que estan marcadas con !alive si no estan
         * vivas
         * */

        // dormir(tiempo del tick del sv - tiempo que tarde en llegar acá)

        // Le llega por el broadcast_game_state los jugadores que estan muertos(booleano)
        game.broadcaster.broadcastGame(turn_id.player_id);
        // Le llega por el broadcast_game_state los jugadores que estan muertos(booleano)
        //
        game.worm_handler.check_drown_worms();
        game.worm_handler.checkDeadWorms();
        game.battlefield.destroy_dead_entities();
        game.battlefield.remove_collided_projectiles();

        game.battlefield.step(game.worm_handler);
        game.broadcaster.remove_closed_clients(game.ready_count, game.players);

        std::chrono::time_point<std::chrono::steady_clock> after = std::chrono::steady_clock::now();

        elapsed_seconds = std::chrono::milliseconds(EST_TICK_TIME) - (after - before);

        std::this_thread::sleep_for(elapsed_seconds);
    }

    erase_id_queue.push(this->game_id);
}
