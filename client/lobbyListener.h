#ifndef LOBBY_LISTENER_H
#define LOBBY_LISTENER_H

#include <map>
#include <memory>
#include <vector>

#include <stdint.h>

#include "../common/States.h"
#include "../common/queue.h"

class PlayerFrame;
class GameFrame;

class LobbyListener {

public:
    static void setGameFrames(std::vector<std::unique_ptr<GameFrame>>& games,
                              Queue<std::shared_ptr<States>>& lobby_states, const uint8_t& games_q);

    static uint8_t getGameFramesQuantity(Queue<std::shared_ptr<States>>& lobby_states);

    static uint8_t getPlayersInLobbyQuantity(Queue<std::shared_ptr<States>>& lobby_states);

    static void setPlayers(std::map<uint8_t, std::unique_ptr<PlayerFrame>>& players,
                           Queue<std::shared_ptr<States>>& lobby_states, const uint8_t& players_q);
};


#endif
