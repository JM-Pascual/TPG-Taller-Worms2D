#include <unistd.h>

#include "game_loop.h"
#include "player_action.h"
#include "../common/GameState.h"
#include "sclient.h"

Queue<std::shared_ptr<PlayerAction>>& GameLoop::get_event_queue() { return this->event_queue; }

void GameLoop::add_client_queue(Queue<GameState>& client_state_queue) {
    this->game.add_client_queue(client_state_queue);
}

void GameLoop::run() {
    while (1) { // ToDo Aca se podria meter un bool que se cambia con un comando exit
        std::shared_ptr<PlayerAction> c;
        if (event_queue.try_pop(c)) {
            c->execute(game);
        }
        game.broadcast_game_state();
        //dormir(tiempo del tick del sv - tiempo que tarde en llegar acá)
        sleep(1);
    }
}
// void GameLoop::killAll() {
//     std::lock_guard<std::mutex> lock(m);
//     for (const auto& [id, client]: clients) {
//         client->kill();
//     }
// }

GameLoop::~GameLoop() {}
