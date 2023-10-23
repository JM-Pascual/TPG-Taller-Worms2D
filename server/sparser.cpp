#include "sparser.h"

#include "../common/const.h"

#include "command.h"
#include "sprotocol.h"

std::unique_ptr<Command> ServerSide::Parser::makeGameCommand(const Commands& c,
                                                             ServerSide::Protocol& protocol) {
    switch (c) {
        case Commands::MOVE:
            return std::make_unique<Move>(
                    1, protocol);  // El 1 seria la id que todavia no la estaria pasando
            break;

        case Commands::JUMP:
            break;

        default:
            break;
    }
    return std::make_unique<Move>(
            0, protocol);  // Momentaneo, faltaria un nullcommand <ver null pattern>
}

std::unique_ptr<Command> ServerSide::Parser::makeLobbyCommand(const Commands& c,
                                                              ServerSide::Protocol& protocol) {
    switch (c) {
        case Commands::CREATE:
            break;

        case Commands::JOIN:
            break;

        default:
            break;
    }
    return std::make_unique<Move>(0, protocol);
}
