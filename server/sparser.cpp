#include "sparser.h"

#include "../common/const.h"

#include "command.h"
#include "lobby.h"
#include "sprotocol.h"

std::unique_ptr<Command> ServerSide::Parser::makeGameCommand(const Commands& c,
                                                             ServerSide::Protocol& protocol) {
    switch (c) {
        case Commands::MOVE:
            return std::make_unique<Move>(
                    protocol);  // El 1 seria la id que todavia no la estaria pasando
            break;

        case Commands::JUMP:
            break;

        default:
            break;
    }
    return std::make_unique<NullCommand>();
}

std::unique_ptr<Command> ServerSide::Parser::makeLobbyCommand(const Commands& c,
                                                              ServerSide::Protocol& protocol,
                                                              uint8_t client_id, Lobby& lobby) {
    switch (c) {
        case Commands::CREATE:
            return std::make_unique<Create>(client_id, lobby);
            break;

        case Commands::JOIN:
            uint8_t game_id;
            protocol.recvGameID(game_id);
            return std::make_unique<Join>(lobby, client_id, game_id);
            break;

        default:
            break;
    }
    return std::make_unique<NullCommand>();
}
