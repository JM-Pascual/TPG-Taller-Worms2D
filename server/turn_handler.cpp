#include "turn_handler.h"

#include <iostream>

const std::pair<uint8_t, bool> TurnHandler::update(uint8_t players_quantity,
                                                   const std::chrono::duration<float>& elapsed) {

    // Adapto el size a los index del map
    players_quantity--;

    // Primer turno
    if (first_turn) {
        first_turn = false;
        return std::make_pair(player_turn, TIMER_RESET);
    }

    // Desconecta un player
    if (players_quantity != current_players_quantity) {
        current_players_quantity = players_quantity;
        return std::make_pair(player_turn, TIMER_RESET);
    }

    elapsed_time += elapsed;

    if (player_stop_action) {
        if (elapsed_time.count() < POST_TURN_DURATION_IN_SECONDS) {
            return std::make_pair(player_turn, NOT_RESET);
        }
    } else {
        // No paso el turno
        if (elapsed_time.count() < TURN_DURATION_IN_SECONDS) {
            return std::make_pair(player_turn, NOT_RESET);
        }
    }

    player_turn++;
    player_stop_action = false;
    elapsed_time = std::chrono::duration<float>(0);


    if (player_turn > players_quantity) {
        player_turn = 0;
    }

    return std::make_pair(player_turn, TIMER_RESET);
}

const bool& TurnHandler::player_used_stop_action() { return player_stop_action; }

void TurnHandler::use_stop_action() {
    player_stop_action = true;

    elapsed_time = std::chrono::duration<float>(0);
}
