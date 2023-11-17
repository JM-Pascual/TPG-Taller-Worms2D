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


        /*
         * Step -> Hago el step y marco como !alive las entidades físicas relacionadas
         * Hago el broad_cast para comunicar el estado a de todas las entidaddes del juego
         * Elimino las entidades de box2d
         * Elimino las entidades físicas relacionadas, que estan marcadas con !alive si no estan
         * vivas
         * */


        // dormir(tiempo del tick del sv - tiempo que tarde en llegar acá)

        game.broadcast_game_state();
        // Le llega por el broadcast_game_state los jugadores que estan muertos(booleano)
        //
        game.remove_box2d_entities();
        game.remove_collided_projectiles();
        game.remove_closed_clients();

        game.step();

        std::chrono::time_point<std::chrono::system_clock> after = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds =
                std::chrono::milliseconds(EST_TICK_TIME) - (after - before);

        std::this_thread::sleep_for(elapsed_seconds);
    }

    erase_id_queue.push(this->game_id);
}
