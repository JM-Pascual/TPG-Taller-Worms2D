#include "cparser.h"

#include <chrono>
#include <thread>

#include "../common/States.h"

void ClientSide::Parser::filterStates(Queue<std::shared_ptr<States>>& game_states,
                                      Queue<std::shared_ptr<States>>& lobby_states,
                                      std::shared_ptr<States> state) {
    switch (state->tag) {
        case StatesTag::GAMES_COUNT_L:
        case StatesTag::INFO_GAME_L:
        case StatesTag::PLAYER_COUNT_L:
        case StatesTag::PLAYER_L:
            lobby_states.push(state);
            break;
        default:
            game_states.push(state);
            break;
    }
}

void ClientSide::Parser::setGameFrames(std::vector<std::unique_ptr<GameFrame>>& games,
                                       Queue<std::shared_ptr<States>>& lobby_states) {
    std::shared_ptr<States> raw_state = nullptr;
    std::shared_ptr<GameInfoL> game_info = nullptr;
    for (uint8_t i = 0; i < games.capacity(); i++) {
        do {
            while (not lobby_states.try_pop(raw_state)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 30));
            }
        } while (game_info->tag != StatesTag::INFO_GAME_L);
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

    std::cout << "1\n";

    return std::dynamic_pointer_cast<GamesCountL>(raw_state)->quantity;
}
