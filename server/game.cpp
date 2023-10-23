#include "game.h"

#include <algorithm>
#include <utility>

#include "sclient.h"

void Game::notifyAllClients(const uint8_t& dto) {
    std::lock_guard<std::mutex> lock(m);
    for (const auto& [id, client]: clients) {
        client->sendChat(dto);
    }
}

void Game::pushClient(std::unique_ptr<ServerSide::Client> client) {
    std::lock_guard<std::mutex> lock(m);
    clients[client->id] = std::move(client);
}

// Esto lo usaba el cleaner de mi tp2, y quedo cuando lo pase. Supongo que igual ahora con los id
// va a cambiar el tema
// bool Game::deleteDeaths() {
//  std::unique_lock<std::mutex> lock(m_clean);
//  can_delete.wait(lock);
//  std::lock_guard<std::mutex> l(m);

// size_t prev_size = clients.size();

// auto end = std::remove_if(clients.begin(), clients.end(), [](ServerSide::Client* c) {
//     if (!c->isAlive()) {
//         delete c;
//         return true;
//     }
//     return false;
// });

// clients.erase(end, clients.end());

// return (prev_size > clients.size());
//}

void Game::killAll() {
    std::lock_guard<std::mutex> lock(m);
    for (const auto& [id, client]: clients) {
        client->kill();
    }
}

void Game::notifyClean() { can_delete.notify_all(); }

Game::~Game() {}  // Todo RAII
