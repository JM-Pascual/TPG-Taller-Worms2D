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

void GameBrowser::join_game(const uint8_t& game_id_to_join, const uint8_t& id,
                            Queue<std::shared_ptr<GameState>>& state_queue,
                            std::atomic<bool>& succesful_join) {

    std::unique_lock<std::mutex> lck(m);

    if (games.count(game_id_to_join) != 1) {
        spdlog::get("server")->debug("No existe la sala {:d}", game_id_to_join);
    } else {
        if (games[game_id_to_join]->game_started_playing()) {
            return;
        }
        games[game_id_to_join]->add_client_queue(id, state_queue);
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

void GameBrowser::set_player_ready(const uint8_t id, const uint8_t id_game) {
    games[id_game]->set_player_ready(id);
}

const bool GameBrowser::game_started_playing(const uint8_t game_id) {
    if (games.count(game_id) == 1)
        return games[game_id]->game_started_playing();
    return false;
}

GameBrowser::~GameBrowser() {
    for (const auto& [id, game]: games) {
        game->join();
    }
}
