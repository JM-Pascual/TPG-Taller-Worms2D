#include "game.h"

#include <unistd.h>

#include "../common/dto.h"

#include "sclient.h"

void Game::broadcast(const std::shared_ptr<MoveDto>& game_state_dto) {
    std::lock_guard<std::mutex> lock(m);
    for (auto& client_game_state_queue: broadcast_list) {
        client_game_state_queue->push(game_state_dto);
    }
}

Queue<std::shared_ptr<Command>>& Game::get_event_queue() { return this->event_queue; }

void Game::add_client_queue(Queue<std::shared_ptr<MoveDto>>& client_game_state) {
    std::lock_guard<std::mutex> lock(m);
    broadcast_list.push_back(&client_game_state);
}

void Game::run() {
    while (1) { // ToDo Aca se podria meter un bool que se cambia con un comando exit
        std::shared_ptr<Command> c;
        if (event_queue.try_pop(c)) {
            c->execute(*this);
            this->broadcast(get_game_state());
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

MoveDto Game::get_game_state() { return MoveDto(player.x, player.y, player.is_walking, player.facing_right); }

Game::~Game() {}
