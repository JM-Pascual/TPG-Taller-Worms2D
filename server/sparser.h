#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H

#include <atomic>
#include <memory>

#include "../common/queue.h"

class Dto;
class Command;
class LobbyCommand;
class GameBrowser;
enum class Commands;

namespace ServerSide {

class Protocol;

class Parser {
public:
    static std::shared_ptr<Command> makeGameCommand(const Commands& c, ServerSide::Protocol&);

    static std::shared_ptr<LobbyCommand> makeLobbyCommand(const Commands& c, ServerSide::Protocol&,
                                                          GameBrowser& gb,
                                                          std::atomic<bool>& connected_to_room,
                                                          uint8_t& game_id,
                                                          Queue<std::unique_ptr<Dto>>& game_state);
};
}  // namespace ServerSide


#endif
