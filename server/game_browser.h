#ifndef WORMS2D_GB_H
#define WORMS2D_GB_H

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../common/queue.h"
#include "../common/thread.h"

#include "player_action.h"
#include "sclient.h"

class Game;

class GBCleaner: public Thread {
private:
    Queue<uint8_t> game_id_to_clean;
    GameBrowser& gb;
    std::atomic<bool> killed;

public:
    explicit GBCleaner(GameBrowser& gb): Thread(), gb(gb), killed(false) {}

    void kill();

    void run() override;

    ~GBCleaner() override = default;

    friend class GameBrowser;
};


class GameBrowser {
private:
    std::mutex m;
    std::map<uint8_t, std::shared_ptr<Game>> games;
    uint8_t game_id_count;
    GBCleaner cleaner;

    /*

    */
    void erase_game(const uint8_t& game_id);

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
    void join_game(const uint8_t& game_code, const uint8_t& id,
                   Queue<std::shared_ptr<States>>& state_queue);
    /*

    */

    Queue<std::shared_ptr<PlayerAction>>& getQueue(const uint8_t& game_id);

    void infoGames(std::vector<std::string>&);
    /*

    */
    void set_player_ready(const uint8_t id, const uint8_t id_game);
    /*

    */
    const bool game_started_playing(const uint8_t game_id);
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

    friend class GBCleaner;
};


#endif  // WORMS2D_GB_H
