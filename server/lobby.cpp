#include "lobby.h"

#include <utility>

#include "lobby_client.h"

Lobby::Lobby(): cleaner(*this), killed(false) { cleaner.start(); }

uint8_t Lobby::createGame() { return gb.create_game(); }

void Lobby::joinGame(const uint8_t& game_code, std::unique_ptr<LobbyClient>& client) {
    gb.join_game(game_code, client);
    erase_client.push(client->id);
    cv_clients.notify_all();
}

void Lobby::infoGames(std::vector<std::string>& info) { gb.infoGames(info); }

void Lobby::pushLobbyClient(std::unique_ptr<LobbyClient> client, uint8_t id) {
    std::unique_lock<std::mutex> lck(m);
    waiting_clients[id] = std::move(client);
    waiting_clients[id]->start();
}

void Lobby::killAll() {
    std::unique_lock<std::mutex> lck(m);

    killed = true;

    cleaner.kill();
    erase_client.close();

    for (const auto& [id, client]: waiting_clients) {
        client->kill();
    }

    gb.killAll();
}

void Lobby::eraseClient() {
    uint8_t client_id;
    std::unique_lock<std::mutex> lck(m_clients);

    while (not erase_client.try_pop(client_id)) {
        cv_clients.wait(lck);
    }

    waiting_clients[client_id]->join();
    waiting_clients.erase(client_id);
}

Lobby::~Lobby() {
    std::unique_lock<std::mutex> lck(m_clients);

    if (not killed) {
        erase_client.close();
    }

    for (const auto& [id, client]: waiting_clients) {
        client->kill();
        client->join();
    }

    cleaner.join();
}

//------------------------------ LOBBY_CLEANER ----------------------------------

Lobby_::Cleaner::Cleaner(Lobby& lobby): Thread(), killed(false), lobby(lobby) {}

void Lobby_::Cleaner::run() {
    try {
        do {
            lobby.eraseClient();
        } while (_keep_running);

    } catch (const ClosedQueue& e) {
        if (!killed) {
            // log
        }
    }
}

void Lobby_::Cleaner::kill() {
    _keep_running = false;
    killed = true;
}
