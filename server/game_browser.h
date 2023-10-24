#ifndef WORMS2D_GB_H
#define WORMS2D_GB_H

#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <stdint.h>

#include "../common/queue.h"

#include "game.h"
#include "lobby_client.h"
#include "sclient.h"

class GameBrowser {
private:
    std::mutex m;
    std::map<uint8_t, std::unique_ptr<Game>> games;
    uint8_t game_id_count;

public:
    /*
        Inicializa el conteo de las id de Game en 0 (game_id_count)
    */
    GameBrowser();
    /*

    */
    uint8_t create_game();
    /*
        Agrega client al Game especificado por game_code
    */
    void join_game(const uint8_t& game_code, std::unique_ptr<LobbyClient>& client);
    /*

    */
    void infoGames(std::vector<std::string>&);
    /*

    */
    void killAll();
    /*

    */
    ~GameBrowser();
    /*
     *  No queremos ni copiar ni mover el monitor
     */
    GameBrowser(const GameBrowser&) = delete;
    GameBrowser& operator=(const GameBrowser&) = delete;

    GameBrowser(GameBrowser&&) = delete;
    GameBrowser& operator=(GameBrowser&&) = delete;
};


#endif  // WORMS2D_LOBBY_H
