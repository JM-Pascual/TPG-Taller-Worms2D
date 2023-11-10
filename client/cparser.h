#ifndef CLIENT_PARSER_H
#define CLIENT_PARSER_H

#include <map>
#include <memory>
#include <vector>

#include "../common/const.h"
#include "../common/queue.h"

#include "mainwindow.h"

class States;
class GameFrame;
class PlayerFrame;

namespace ClientSide {

class Parser {

public:
    static void filterStates(Queue<std::shared_ptr<States>>& game_states,
                             Queue<std::shared_ptr<States>>& lobby_states,
                             std::shared_ptr<States> state);

    static void setGameFrames(std::vector<std::unique_ptr<GameFrame>>& games,
                              Queue<std::shared_ptr<States>>& lobby_states, const uint8_t& games_q);

    static uint8_t getGameFramesQuantity(Queue<std::shared_ptr<States>>& lobby_states);

    static uint8_t getPlayersInLobbyQuantity(Queue<std::shared_ptr<States>>& lobby_states);

    static void setPlayers(std::map<uint8_t, std::unique_ptr<PlayerFrame>>& players,
                           Queue<std::shared_ptr<States>>& lobby_states, const uint8_t& players_q);
};
}  // namespace ClientSide

#endif
