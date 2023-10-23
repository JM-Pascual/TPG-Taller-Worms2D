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
    std::unique_ptr<Command> makeCommand(const Commands&, ServerSide::Protocol&);
};
}  // namespace ServerSide


#endif
