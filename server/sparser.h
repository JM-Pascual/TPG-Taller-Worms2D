#ifndef SERVER_PARSER_H
#define SERVER_PARSER_H

#include <memory>

class Command;
enum class Commands;

namespace ServerSide {

class Protocol;

class Parser {

private:
public:
    std::unique_ptr<Command> makeGameCommand(const Commands&, ServerSide::Protocol&);

    std::unique_ptr<Command> makeLobbyCommand(const Commands&, ServerSide::Protocol&);
};
}  // namespace ServerSide


#endif
