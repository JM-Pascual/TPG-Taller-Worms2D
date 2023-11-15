#ifndef TURN_HANDLER_H
#define TURN_HANDLER_H

#include <chrono>
#include <utility>

#include <stdint.h>

#define TURN_DURATION_IN_SECONDS 10

#define TIMER_RESET true
#define NOT_RESET false

class TurnHandler {
private:
    uint8_t player_turn;
    bool first_turn;
    std::chrono::duration<float> elapsed_time;
    uint8_t current_players_quantity;

public:
    TurnHandler(): player_turn(0), first_turn(true), current_players_quantity(0) {}

    const std::pair<uint8_t, bool> update(uint8_t players_quantity,
                                          const std::chrono::duration<float>& elapsed);
};

#endif
