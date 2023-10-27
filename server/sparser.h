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

private:
public:
    std::unique_ptr<Command> makeGameCommand(const Commands& c, ServerSide::Protocol&);

    std::unique_ptr<Command> makeLobbyCommand(const Commands& c, ServerSide::Protocol&,
                                              uint8_t client_id, const GameBrowser& gb,
                                              std::atomic<bool>& joined_game,
                                              Queue<uint8_t>& game_queue);
};
}  // namespace ServerSide


#endif
