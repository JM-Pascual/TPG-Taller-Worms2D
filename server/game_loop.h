#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include <memory>
#include <string>

#include <stdint.h>

#include "../common/queue.h"
#include "../common/thread.h"

#include "player_action.h"

#define TICK_RATE 30
#define EST_TICK_TIME 1000 / TICK_RATE

class Game;

class GameLoop: public Thread {
private:
    Queue<std::shared_ptr<PlayerAction>> action_queue;
    Game& game;

public:
    explicit GameLoop(Game& game): game(game) {}

    Queue<std::shared_ptr<PlayerAction>>& get_action_queue();

    void run() override;

    // Libera los recursos de todos los clientes
    ~GameLoop() override = default;

    // No queremos ni copiar ni mover el monitor
    GameLoop(const GameLoop&) = delete;
    GameLoop& operator=(const GameLoop&) = delete;

    GameLoop(GameLoop&&) = delete;
    GameLoop& operator=(GameLoop&&) = delete;
};


#endif
