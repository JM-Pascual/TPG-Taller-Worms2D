#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <memory>
#include <string>

#include <stdint.h>

#include "../common/queue.h"
#include "../common/thread.h"

#include "Game.h"
#include "player_action.h"

class GameLoop: public Thread {
private:
    Queue<std::shared_ptr<PlayerAction>> action_queue;
    Game game;

public:
    // Crea la lista de clientes vacia
    GameLoop() = default;

    Queue<std::shared_ptr<PlayerAction>>& get_action_queue();

    void run() override;

    void add_client_queue(const uint8_t& id, Queue<std::shared_ptr<GameState>>& state_queue);

    void set_player_ready(const uint8_t id);

    const bool game_started_playing();

    // Libera los recursos de todos los clientes
    ~GameLoop() override;

    // No queremos ni copiar ni mover el monitor
    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;

    GameLoop(GameLoop&&) = delete;
    GameLoop& operator=(GameLoop&&) = delete;
};


#endif
