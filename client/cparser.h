#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H

#include <memory>
#include <vector>

#include "../common/queue.h"

#include "mainwindow.h"

class States;
class GameFrame;

namespace ClientSide {

class Parser {

public:
    static void filterStates(Queue<std::shared_ptr<States>>& game_states,
                             Queue<std::shared_ptr<States>>& lobby_states,
                             std::shared_ptr<States> state);

    static void setGameFrames(std::vector<std::unique_ptr<GameFrame>>& games,
                              Queue<std::shared_ptr<States>>& lobby_states);

    static uint8_t getGameFramesQuantity(Queue<std::shared_ptr<States>>& lobby_states);
};
}  // namespace ClientSide

#endif
