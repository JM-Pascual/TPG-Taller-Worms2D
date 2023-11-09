#include "game_browser.h"

#include <spdlog/spdlog.h>

#include "Game.h"

GameBrowser::GameBrowser(): game_id_count(0), cleaner(*this) { cleaner.start(); }

void GameBrowser::create_game(const std::string& desc, const std::string& map,
                              uint8_t& game_id_to_create) {
    std::unique_lock<std::mutex> lck(m);

    games.insert({game_id_count,
                  std::make_unique<Game>(desc, map, game_id_count, cleaner.game_id_to_clean)});
    game_id_to_create = game_id_count++;
    // Post Incremento para devolver el valor anterior y luego inc

    spdlog::get("server")->info("Se creo la sala de juego {:d}", game_id_to_create);
}

void GameBrowser::join_game(const uint8_t& game_id_to_join, const uint8_t& id,
                            Queue<std::shared_ptr<States>>& state_queue) {

    std::unique_lock<std::mutex> lck(m);

    if (games.count(game_id_to_join) != 1) {
        spdlog::get("server")->error("No existe el juego {:d}", game_id_to_join);
        return;
    }

    if (games.at(game_id_to_join)->is_playing()) {
        spdlog::get("server")->warn("El juego {:d} ya empezo!", game_id_to_join);
        return;
    }

    games.at(game_id_to_join)->add_client_queue(id, state_queue);
    spdlog::get("server")->debug("Cliente asignado a la sala {:d}", game_id_to_join);
}

Queue<std::shared_ptr<PlayerAction>>& GameBrowser::getQueue(const uint8_t& game_id) {
    std::unique_lock<std::mutex> lck(m);
    if (games.count(game_id) == 1 ? games.at(game_id)->is_playing() : false)
        return games.at(game_id)->get_action_queue();
    throw NonExistingQueue();
}

void GameBrowser::infoGames(std::vector<std::shared_ptr<GameInfoL>>& info) {
    std::unique_lock<std::mutex> lck(m);

    spdlog::get("server")->debug("Recolectando informacion de los juegos en ejecucion");
    info.resize(games.size());
    for (const auto& [id, game]: games) {
        info.push_back(game->getInfo());
    }
}

void GameBrowser::set_player_ready(const uint8_t id, const uint8_t id_game) {
    std::unique_lock<std::mutex> lck(m);
    if (games.count(id_game) != 1) {
        return;
    }

    games.at(id_game)->set_player_ready(id);
    spdlog::get("server")->debug("Jugador {:d} cambio estado ready en juego {:d}", id, id_game);
}

const bool GameBrowser::game_started_playing(const uint8_t game_id) {
    std::unique_lock<std::mutex> lck(m);
    return (games.count(game_id) == 1 ? games.at(game_id)->is_playing() : false);
    // Si el juego existe retorna si estan jugando, false en otro caso
}

void GameBrowser::erase_game(const uint8_t& game_id) {
    std::unique_lock<std::mutex> lck(m);
    games.erase(game_id);
}

GameBrowser::~GameBrowser() {
    cleaner.kill();
    cleaner.join();
}

// -------------- GB CLEANER -------------------

void GBCleaner::kill() {
    killed = true;
    this->stop();
    this->game_id_to_clean.close();
}

void GBCleaner::run() try {
    while (_keep_running) {
        gb.erase_game(game_id_to_clean.pop());
    }

} catch (const ClosedQueue& e) {
    if (not killed) {
        spdlog::get("server")->error("Se cerro la queue de GBCleaner");
    }
}
