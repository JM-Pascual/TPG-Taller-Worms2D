#ifndef WORMS2D_LOBBY_H
#define WORMS2D_LOBBY_H

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
    /*
        Ambos uint8_t son usados como ids, por lo cual el maximo de games / clientes esperando es
       256
    */
    std::map<uint8_t, std::unique_ptr<Game>> games;
    std::map<uint8_t, std::unique_ptr<LobbyClient>> waiting_clients;
    uint8_t game_id_count;

public:
    GameBrowser();
    uint8_t create_game();

    void join_game(uint8_t game_code, std::unique_ptr<LobbyClient>& client);
    /*

    */
    void infoGames(std::vector<std::string>&);
    /*

    */
    void pushLobbyClient(std::unique_ptr<LobbyClient>, uint8_t id);
    /*

    */
    void killAll();
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
