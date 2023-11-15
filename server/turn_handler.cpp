#include "turn_handler.h"

#include <iostream>

const std::pair<uint8_t, bool> TurnHandler::update(const uint8_t& players_quantity,
                                                   const std::chrono::duration<float>& elapsed) {

    if (first_turn) {
        first_turn = false;
        return std::make_pair(player_turn, TIMER_RESET);
    }

    elapsed_time += elapsed;

    if (std::chrono::duration_cast<std::chrono::seconds>(elapsed_time).count() <
        TURN_DURATION_IN_SECONDS) {
        return std::make_pair(player_turn, NOT_RESET);
    }

    player_turn++;
    elapsed_time = std::chrono::duration<float>(0);


    if (player_turn > players_quantity) {
        player_turn = 0;
    }

    return std::make_pair(player_turn, TIMER_RESET);
}
