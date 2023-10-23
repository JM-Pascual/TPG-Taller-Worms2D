#include "lobby.h"

Lobby::Lobby() = default;

void Lobby::create_game(uint8_t game_code, ServerSide::Client* client) {
    auto* game = new Game();
    game->pushClient(client);
    std::unique_lock<std::mutex> lck(m);
    games.insert(std::pair<uint8_t,Game*>(game_code, game));
}

void Lobby::join_game(uint8_t game_code, ServerSide::Client* client) {
    std::unique_lock<std::mutex> lck(m);
    if(games.count(game_code) > 0){ //Solo puede llegar a ver una solo elemento con esa llave, ver si cambio a == 1.
        games.at(game_code)->pushClient(client);
    }
}
//Ver si lo dejo acá el destructor o lo tengo que hacer cuando hago el kill
Lobby::~Lobby() {
    std::unique_lock<std::mutex> lck(m);
    for (auto const& x : games) {
        delete x.second;
    }
    games.clear();
}
