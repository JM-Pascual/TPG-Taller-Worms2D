#include "turn_handler.h"

#include "Player.h"
#include "broadcaster.h"
#include "worm_handler.h"


const bool TurnHandler::need_to_update(uint8_t players_quantity,
                                       const std::chrono::duration<float>& elapsed) {

    // Adapto el size a los index del map
    players_quantity--;

    // Primer turno
    if (first_turn) {
        first_turn = false;
        return TIMER_RESET;
    }

    // Desconecta un player
    if (players_quantity != current_players_quantity) {
        current_players_quantity = players_quantity;
        return TIMER_RESET;
    }

    elapsed_time += elapsed;

    if (player_stop_action) {
        if (elapsed_time.count() < POST_TURN_DURATION_IN_SECONDS) {
            return NOT_RESET;
        }
    } else {
        // No paso el turno
        if (elapsed_time.count() < TURN_DURATION_IN_SECONDS) {
            return NOT_RESET;
        }
    }

    player_turn++;
    player_stop_action = false;
    elapsed_time = std::chrono::duration<float>(0);


    if (player_turn > players_quantity) {
        player_turn = 0;
        for (auto& [id, player]: players) {
            if (++player->worm_turn > (player->worms.size() - 1)) {
                player->worm_turn = 0;
            }
        }
    }

    return TIMER_RESET;
}

const ActualTurn TurnHandler::updateTurn(const std::chrono::duration<float>& elapsed,
                                         BroadCaster& broadcaster, WormHandler& worm_handler) {
    if (not this->need_to_update(players.size(), elapsed)) {  // Si resetea el timer
        return ActualTurn(prev_player_turn_id, players.at(prev_player_turn_id)->worm_turn);
    }

    auto it = players.begin();
    std::advance(it, player_turn);
    uint8_t player_id = it->first;

    // Enviar solo si cambio el turno (o sea reseteo el timer)
    if (player_id != prev_player_turn_id) {
        worm_handler.stop_all_players();
        broadcaster.broadcast_turn(player_turn);
    }

    prev_player_turn_id = player_id;
    return ActualTurn(
            player_id,
            players.at(player_id)->worm_turn);  // Retorno la id del jugador el cual es su turno
}

const bool& TurnHandler::player_used_stop_action() { return player_stop_action; }

void TurnHandler::use_stop_action() {
    player_stop_action = true;

    elapsed_time = std::chrono::duration<float>(0);
}
