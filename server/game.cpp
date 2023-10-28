#include "game.h"

#include <algorithm>
#include <utility>

#include <unistd.h>

#include "../common/dto.h"

#include "sclient.h"

Game::Game(): x(0) {}

void Game::broadcast(const std::unique_ptr<Dto>& dto) {
    std::lock_guard<std::mutex> lock(m);
    for (auto& client_gstate: broadcast_list) {
        client_gstate->push(dto);
    }
}

Queue<std::shared_ptr<Command>>& Game::get_event_queue() { return this->event_queue; }

void Game::add_client_queue(Queue<std::unique_ptr<Dto>>& client_game_state) {
    std::lock_guard<std::mutex> lock(m);
    broadcast_list.push_back(&client_game_state);
}

void Game::run() {
    while (1) { // ToDo Aca se podria meter un bool que se cambia con un comando exit
        std::shared_ptr<Command> c;
        if (event_queue.try_pop(c)) {
            c->execute(*this);
            //this->broadcast(x);
        }
        sleep(1);
    }
}
// void Game::killAll() {
//     std::lock_guard<std::mutex> lock(m);
//     for (const auto& [id, client]: clients) {
//         client->kill();
//     }
// }

Game::~Game() {}  // Todo RAII
