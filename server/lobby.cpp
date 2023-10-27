#include "lobby.h"

#include <utility>

#include <spdlog/spdlog.h>


Lobby::Lobby(): killed(false), cleaner(*this) { cleaner.start(); }

uint8_t Lobby::createGame() { return gb.create_game(); }

void Lobby::joinGame(const uint8_t& game_code, const uint8_t& client_id) {
    gb.join_game(game_code, waiting_clients[client_id]);
    erase_client.push(client_id);
}

void Lobby::infoGames(std::vector<std::string>& info) { gb.infoGames(info); }

void Lobby::pushLobbyClient(std::unique_ptr<LobbyClient> client, uint8_t id) {
    std::unique_lock<std::mutex> lck(m);
    waiting_clients[id] = std::move(client);
    spdlog::get("server")->debug("Cliente {:d} aniadido al lobby, iniciando su hilo", id);
    waiting_clients[id]->start();
    spdlog::get("server")->debug("Hilo del cliente {:d} iniciado con exito", id);
}

void Lobby::killAll() {
    std::unique_lock<std::mutex> lck(m);

    cleaner.kill();
    spdlog::get("server")->debug("Cerrando queue de clientes lobby a eliminar");
    erase_client.close();

    for (const auto& [id, client]: waiting_clients) {
        client->kill();
    }

    gb.killAll();

    killed = true;
}

void Lobby::eraseClient() {
    uint8_t client_id = erase_client.pop();

    std::unique_lock<std::mutex> lck(m);
    spdlog::get("server")->debug("Joineando cliente {:d}", client_id);
    waiting_clients[client_id]->join();
    spdlog::get("server")->debug("Eliminando cliente {:d}", client_id);
    waiting_clients.erase(client_id);
}

Lobby::~Lobby() {
    // Sin Lock, ya que si se esta llamando a este destructor no se van a aniadir ni eliminar nuevos
    // clientes

    if (not killed) {
        this->killAll();
    }

    for (const auto& [id, client]: waiting_clients) {
        spdlog::get("server")->debug("Joineando cliente {:d}", id);
        client->join();
    }
    spdlog::get("server")->debug("Joineando cleaner");
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
            spdlog::get("server")->error("Se cerro la queue de clientes lobby a eliminar");
        }
    }
}

void Lobby_::Cleaner::kill() {
    _keep_running = false;
    killed = true;
}
