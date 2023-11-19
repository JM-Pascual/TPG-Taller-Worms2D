#ifndef TURN_HANDLER_H
#define TURN_HANDLER_H

#include <chrono>
#include <map>
#include <memory>
#include <utility>

#include <stdint.h>

#define TURN_DURATION_IN_SECONDS 10
#define POST_TURN_DURATION_IN_SECONDS 3

#define TIMER_RESET true
#define NOT_RESET false


struct ActualTurn {
public:
    const uint8_t player_id;
    const uint8_t worm_index;

    ActualTurn(const uint8_t& player_id, const uint8_t& worm_index):
            player_id(player_id), worm_index(worm_index) {}
};

class Player;
class WormHandler;
class BroadCaster;


class TurnHandler {
private:
    uint8_t player_turn;
    bool first_turn;
    std::chrono::duration<float> elapsed_time;

    std::map<uint8_t, std::unique_ptr<Player>>& players;
    uint8_t current_players_quantity;

    bool player_stop_action;

    // int16_t para poder iniciarlo en -1 y que se tome bien el proximo turno
    int16_t prev_player_turn_id;

    const bool need_to_update(uint8_t players_quantity, const std::chrono::duration<float>& elapsed,
                              WormHandler& worm_handler);

    void advanceTurn(const uint8_t& players_quantity, WormHandler& worm_handler);

public:
    explicit TurnHandler(std::map<uint8_t, std::unique_ptr<Player>>& players):
            player_turn(0),
            first_turn(true),
            elapsed_time(0),
            players(players),
            current_players_quantity(0),
            player_stop_action(false),
            prev_player_turn_id(-1) {}

    const ActualTurn updateTurn(const std::chrono::duration<float>& elapsed,
                                BroadCaster& broadcaster, WormHandler& worm_handler);

    const bool& player_used_stop_action();

    void use_stop_action();
};

#endif
