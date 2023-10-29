#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H

#include <atomic>
#include <memory>

#include "../common/queue.h"
#include "../common/GameState.h"

class PlayerAction;
class LobbyAction;
class GameBrowser;
enum class Actions;

namespace ServerSide {

class Protocol;

class Parser {
public:
    static std::shared_ptr<PlayerAction> makePlayerAction(const Actions& c, ServerSide::Protocol&);

    static std::shared_ptr<LobbyAction> makeLobbyAction(const Actions& c, ServerSide::Protocol&,
                                                          GameBrowser& browser,
                                                          std::atomic<bool>& connected_to_room,
                                                          uint8_t& game_id,
                                                          Queue<GameState>& game_state);
};
}  // namespace ServerSide


#endif
