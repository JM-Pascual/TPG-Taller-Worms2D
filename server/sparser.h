#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H

#include <memory>

class Command;
class Lobby;
enum class Commands;

namespace ServerSide {

class Protocol;

class Parser {

private:
public:
    std::unique_ptr<Command> makeGameCommand(const Commands& c, ServerSide::Protocol&);

    std::unique_ptr<Command> makeLobbyCommand(const Commands& c, ServerSide::Protocol&,
                                              uint8_t client_id, Lobby& lobby);
};
}  // namespace ServerSide


#endif
