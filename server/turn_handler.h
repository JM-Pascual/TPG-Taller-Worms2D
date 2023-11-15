#ifndef TURN_HANDLER_H
#define TURN_HANDLER_H

#include <chrono>
#include <utility>

#include <stdint.h>

#define TURN_DURATION_IN_SECONDS 60

#define TIMER_RESET true
#define NOT_RESET false

class TurnHandler {
private:
    uint8_t player_turn;
    bool first_turn;
    std::chrono::duration<float> elapsed_time;

public:
    TurnHandler(): player_turn(0), first_turn(true) {}

    const std::pair<uint8_t, bool> update(const uint8_t& players_quantity,
                                          const std::chrono::duration<float>& elapsed);
};

#endif
