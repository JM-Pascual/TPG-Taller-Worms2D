#include "cparser.h"

#include <chrono>
#include <thread>

#include "../common/States.h"

void ClientSide::Parser::filterStates(Queue<std::shared_ptr<States>>& game_states,
                                      Queue<std::shared_ptr<States>>& lobby_states,
                                      std::shared_ptr<States> state) {
    switch (state->tag) {
        case StatesTag::GAMES_COUNT_L:
        case StatesTag::GAME_NOT_JOINABLE:
        case StatesTag::INFO_GAME_L:
        case StatesTag::PLAYER_COUNT_L:
        case StatesTag::PLAYER_L:
        case StatesTag::MY_ID:
            lobby_states.push(state);
            break;
        default:
            game_states.push(state);
            break;
    }
}

void ClientSide::Parser::setGameFrames(std::vector<std::unique_ptr<GameFrame>>& games,
                                       Queue<std::shared_ptr<States>>& lobby_states,
                                       const uint8_t& games_q) {
    std::shared_ptr<States> raw_state = nullptr;
    std::shared_ptr<GameInfoL> game_info = nullptr;
    for (uint8_t i = 0; i < games_q; i++) {
        do {
            while (not lobby_states.try_pop(raw_state)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
            }
        } while (raw_state->tag != StatesTag::INFO_GAME_L);
        game_info = std::dynamic_pointer_cast<GameInfoL>(raw_state);
        games[i]->setFrame(game_info->description, game_info->map, game_info->player_count,
                           game_info->game_id);
        games[i]->show();
    }
}

uint8_t ClientSide::Parser::getGameFramesQuantity(Queue<std::shared_ptr<States>>& lobby_states) {
    std::shared_ptr<States> raw_state = nullptr;

    do {
        while (not lobby_states.try_pop(raw_state)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
        }
    } while (raw_state->tag != StatesTag::GAMES_COUNT_L);

    return std::dynamic_pointer_cast<GamesCountL>(raw_state)->quantity;
}

uint8_t ClientSide::Parser::getPlayersInLobbyQuantity(
        Queue<std::shared_ptr<States>>& lobby_states) {
    std::shared_ptr<States> raw_state = nullptr;

    do {
        while (not lobby_states.try_pop(raw_state)) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
        }
        if (raw_state->tag == StatesTag::GAME_NOT_JOINABLE) {
            break;
        }

    } while (raw_state->tag != StatesTag::PLAYER_COUNT_L);

    return std::dynamic_pointer_cast<CountState>(raw_state)->quantity;
}

void ClientSide::Parser::setPlayers(std::map<uint8_t, std::unique_ptr<PlayerFrame>>& players,
                                    Queue<std::shared_ptr<States>>& lobby_states,
                                    const uint8_t& players_q) {
    std::shared_ptr<States> raw_state = nullptr;
    std::shared_ptr<PlayerStateL> player_info = nullptr;
    for (uint8_t i = 0; i < players_q; i++) {
        do {
            while (not lobby_states.try_pop(raw_state)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
            }
        } while (raw_state->tag != StatesTag::PLAYER_L);
        player_info = std::dynamic_pointer_cast<PlayerStateL>(raw_state);
        players.insert({player_info->id, std::make_unique<PlayerFrame>(player_info->id)});
    }
}
