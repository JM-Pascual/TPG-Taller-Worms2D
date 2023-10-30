#ifndef WORMS2D_GB_H
#define WORMS2D_GB_H

#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../common/queue.h"

#include "game_loop.h"
#include "player_action.h"
#include "sclient.h"

class Dto;

class GameBrowser {
private:
    std::mutex m;
    std::map<uint8_t, std::shared_ptr<GameLoop>> games;
    uint8_t game_id_count;

public:
    /*
        Inicializa el conteo de las id de GameLoop en 0 (game_id_count)
    */
    GameBrowser();
    /*

    */
    void create_game(uint8_t& game_id_to_create);
    /*
        Agrega client al GameLoop especificado por game_code
    */
    void join_game(const uint8_t& game_code, Queue<std::shared_ptr<GameState>>& client_state_queue,
                   std::atomic<bool>& succesful_join);
    /*

    */

    Queue<std::shared_ptr<PlayerAction>>& getQueue(const uint8_t& game_id);

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


#endif  // WORMS2D_GB_H
