#include "sparser.h"

#include "../common/const.h"

#include "command.h"
#include "game_browser.h"
#include "sprotocol.h"

std::unique_ptr<Command> ServerSide::Parser::makeGameCommand(const Commands& c,
                                                             ServerSide::Protocol& protocol) {
    switch (c) {
        case Commands::MOVE:
            return std::make_unique<Move>(
                    protocol);  // El 1 seria la id que todavia no la estaria pasando
            break;

        case Commands::JUMP:
            return std::make_unique<NullCommand>();
            break;

        default:
            return std::make_unique<NullCommand>();
            break;
    }
}

std::unique_ptr<Command> ServerSide::Parser::makeLobbyCommand(
        const Commands& c, ServerSide::Protocol& protocol, uint8_t client_id, const GameBrowser& gb,
        std::atomic<bool>& joined_game, Queue<uint8_t>& game_queue) {
    joined_game = true;
    switch (c) {
        case Commands::CREATE:
            return std::make_unique<Create>(client_id, gb, game_queue);
            break;

        case Commands::JOIN:
            uint8_t game_id;
            protocol.recvGameID(game_id);
            return std::make_unique<Join>(gb, client_id, game_id, game_queue);
            break;

        default:
            joined_game = false;
            return std::make_unique<NullCommand>();
            break;
    }
}
