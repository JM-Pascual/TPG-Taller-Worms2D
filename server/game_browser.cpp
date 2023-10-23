#include "game_browser.h"

#include <utility>

GameBrowser::GameBrowser() = default;

uint8_t GameBrowser::create_game() {
    // Por el momento no tiene args, despues tendra nombre, mapa, etc
    std::unique_lock<std::mutex> lck(m);

    uint8_t game_id = games.size();
    games[game_id] = std::make_unique<Game>();

    return game_id;
}

void GameBrowser::join_game(uint8_t game_code, std::unique_ptr<LobbyClient>& client) {

    // Falta joinear el client <LobbyClient>
    // Supongo que vamos a tener que tener un LobbyCleaner y uno por Game

    std::unique_lock<std::mutex> lck(m);
    if (games.count(game_code) == 1) {
        games[game_code]->pushClient(
                std::make_unique<ServerSide::Client>(client.get(), games[game_code]));
        // avisar a la eventual cond_var
    } else {
        // log
        // throw
    }
}

void GameBrowser::infoGames(std::vector<std::string>& info) {
    std::unique_lock<std::mutex> lck(m);
    for (const auto& [id, game]: games) {
        std::string s("Game id: " +
                      std::to_string(id));  // + "players: " + std::to_string(value.playersCount());
        info.push_back(s);
    }
}

void GameBrowser::pushLobbyClient(std::unique_ptr<LobbyClient> client, uint8_t id) {
    std::unique_lock<std::mutex> lck(m);
    waiting_clients[id] = std::move(client);
    waiting_clients[id]->start();
}

void GameBrowser::killAll() {
    std::unique_lock<std::mutex> lck(m);
    for (const auto& [id, game]: games) {
        game->killAll();
    }
}

GameBrowser::~GameBrowser() {
    std::unique_lock<std::mutex> lck(m);

    for (const auto& [id, game]: waiting_clients) {
        game->join();
    }

    games.clear();
}
