#include "game.h"

#include <algorithm>
#include <utility>

#include <unistd.h>

#include "sclient.h"

Game::Game(): x(0) {}

void Game::broadcast(const uint8_t& dto) {
    std::lock_guard<std::mutex> lock(m);
    for (auto& client_gstate: broadcast_list) {
        client_gstate->push(dto);
    }
}

Queue<std::shared_ptr<Command>>& Game::getQueue() { return this->queue; }

void Game::pushQueue(Queue<uint8_t>& client_game_state) {
    broadcast_list.push_back(&client_game_state);
}

void Game::run() {
    while (1)  // Aca se podria meter un bool que se cambia con un comando exit
    {
        std::shared_ptr<Command> c;
        while (queue.try_pop(c)) {
            sleep(10);
        }
        c->execute(*this);
        this->broadcast(x);
    }
}
// void Game::killAll() {
//     std::lock_guard<std::mutex> lock(m);
//     for (const auto& [id, client]: clients) {
//         client->kill();
//     }
// }

Game::~Game() {}  // Todo RAII
