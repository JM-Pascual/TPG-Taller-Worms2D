#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H

#include <atomic>
#include <memory>

class Command;
class GameBrowser;
enum class Commands;

namespace ServerSide {

class Protocol;

class Parser {
public:
    static std::shared_ptr<Command> makeGameCommand(const Commands& c, ServerSide::Protocol&);

    static std::shared_ptr<Command> makeLobbyCommand(const Commands& c, ServerSide::Protocol&,
                                              GameBrowser& gb,
                                              std::atomic<bool>& joined_game,
                                              uint8_t& game_id);
};
}  // namespace ServerSide


#endif
