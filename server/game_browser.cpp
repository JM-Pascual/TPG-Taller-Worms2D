#include "game_browser.h"

#include <spdlog/spdlog.h>

GameBrowser::GameBrowser(): game_id_count(0) {}

void GameBrowser::create_game(uint8_t& game_id_to_create) {
    // Por el momento no tiene args, despues tendra nombre, mapa, etc
    std::unique_lock<std::mutex> lck(m);

    games[game_id_count] = std::make_unique<GameLoop>();

    game_id_to_create =
            game_id_count++;  // Post Incremento para devolver el valor anterior y luego inc

    spdlog::get("server")->info("Se creo la sala de juego {:d}", (game_id_to_create));
}

void GameBrowser::join_game(const uint8_t& game_id_to_join,
                            Queue<std::shared_ptr<WormGameState>>& client_state_queue,
                            std::atomic<bool>& succesful_join) {

    std::unique_lock<std::mutex> lck(m);

    if (games.count(game_id_to_join) != 1) {
        spdlog::get("server")->debug("No existe la sala {:d}", game_id_to_join);
    } else {
        games[game_id_to_join]->add_client_queue(client_state_queue);
        spdlog::get("server")->debug("Cliente asignado a la sala {:d}", game_id_to_join);
        succesful_join = true;
    }
}

Queue<std::shared_ptr<PlayerAction>>& GameBrowser::getQueue(const uint8_t& game_id) {
    std::unique_lock<std::mutex> lck(m);
    return games[game_id]->get_action_queue();
}

void GameBrowser::infoGames(std::vector<std::string>& info) {
    std::unique_lock<std::mutex> lck(m);

    spdlog::get("server")->debug("Recolectando informacion de los juegos en ejecucion");
    for (const auto& [id, game]: games) {
        std::string s("GameLoop id: " +
                      std::to_string(id));  // + "players: " + std::to_string(value.playersCount());
        info.push_back(s);
    }
}

GameBrowser::~GameBrowser() {
    for (const auto& [id, game]: games) {
        game->join();
    }
}
