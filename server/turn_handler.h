#ifndef TURN_HANDLER_H
#define TURN_HANDLER_H

#include <chrono>
#include <map>
#include <memory>
#include <utility>

#include <stdint.h>

#define TURN_DURATION_IN_SECONDS 10
#define POST_TURN_DURATION_IN_SECONDS 3

#define BLOCK_PLAYERS_INPUT true

enum class TurnReset { NOT_RESET = 0, TIMER_RESET = 1, WAIT_TURN_END = 2 };


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
    std::chrono::duration<float> elapsed_time;

    std::map<uint8_t, std::unique_ptr<Player>>& players;
    uint8_t current_players_quantity;

    bool player_stop_action;

    const TurnReset need_to_update(const uint8_t players_quantity,
                                   const std::chrono::duration<float>& elapsed,
                                   WormHandler& worm_handler, const bool& battlefield_empty);

    const TurnReset advanceTurn(const uint8_t& players_quantity, WormHandler& worm_handler,
                                const bool& battlefield_empty);

public:
    explicit TurnHandler(std::map<uint8_t, std::unique_ptr<Player>>& players):
            player_turn(0),
            elapsed_time(0),
            players(players),
            current_players_quantity(0),
            player_stop_action(false) {}

    const ActualTurn updateTurn(const std::chrono::duration<float>& elapsed,
                                BroadCaster& broadcaster, WormHandler& worm_handler,
                                const bool& battlefield_empty);

    const bool& player_used_stop_action();

    void use_stop_action();
};

#endif
