#include "game_browser.h"

#include <spdlog/spdlog.h>

GameBrowser::GameBrowser(): game_id_count(0) {}

void GameBrowser::create_game(uint8_t& game_id_to_create) {
    // Por el momento no tiene args, despues tendra nombre, mapa, etc
    std::unique_lock<std::mutex> lck(m);

    games[game_id_count] = std::make_unique<Game>();
    game_id_to_create = game_id_count;

    game_id_count++;
}

Queue<uint8_t>& GameBrowser::join_game(const uint8_t& game_id_to_join) {
    std::unique_lock<std::mutex> lck(m);

    if (games.find(game_id_to_join) == games.end()) {
        spdlog::get("server")->debug("No existe la sala {:d}", game_id_to_join);
        //Handle room no existente
    } else {
        spdlog::get("server")->debug("Cliente asignado a la sala {:d}", game_id_to_join);
    }

}

Queue<std::shared_ptr<Command>>& GameBrowser::getQueue(const uint8_t& game_id) { return games[game_id]->getQueue(); }

void GameBrowser::infoGames(std::vector<std::string>& info) {
    std::unique_lock<std::mutex> lck(m);

    spdlog::get("server")->debug("Recolectando informacion de los juegos en ejecucion");
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
GameBrowser::~GameBrowser() {}
