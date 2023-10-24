#include "game_browser.h"

#include <utility>

GameBrowser::GameBrowser(): game_id_count(0) {}

uint8_t GameBrowser::create_game() {
    // Por el momento no tiene args, despues tendra nombre, mapa, etc
    std::unique_lock<std::mutex> lck(m);

    games[game_id_count] = std::make_unique<Game>();

    return game_id_count++;  // Pos incremento para devolver el valor anterior al incremento
}

void GameBrowser::join_game(const uint8_t& game_code, std::unique_ptr<LobbyClient>& client) {
    std::unique_lock<std::mutex> lck(m);
    if (games.count(game_code) == 1) {
        games[game_code]->pushClient(
                std::make_unique<ServerSide::Client>(client.get(), games[game_code]));
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

void GameBrowser::killAll() {
    std::unique_lock<std::mutex> lck(m);

    for (const auto& [id, game]: games) {
        game->killAll();
    }
}

GameBrowser::~GameBrowser() {
    std::unique_lock<std::mutex> lck(m);

    games.clear();
}
