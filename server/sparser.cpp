#include "sparser.h"

#include "../common/const.h"

#include "command.h"
#include "game_browser.h"
#include "sprotocol.h"

std::shared_ptr<Command> ServerSide::Parser::makeGameCommand(const Commands& c,
                                                             ServerSide::Protocol& protocol) {
    switch (c) {
        case Commands::MOVE:
            return std::make_shared<Move>(
                    protocol);  // El 1 seria la id que todavia no la estaria pasando

        case Commands::JUMP:
            return std::make_shared<NullCommand>();

        default:
            return std::make_shared<NullCommand>();
    }
}
std::shared_ptr<Command> ServerSide::Parser::makeLobbyCommand(
        const Commands& c, ServerSide::Protocol& protocol, GameBrowser& gb,
        std::atomic<bool>& joined_game, uint8_t& game_id) {
    joined_game = true;
    switch (c) {
        case Commands::CREATE:
            return std::make_shared<Create>(gb, game_id);

        case Commands::JOIN:
            uint8_t id_to_join;
            protocol.recvGameID(id_to_join);
            return std::make_shared<Join>(gb, game_id);

        default:
            joined_game = false;
            return std::make_shared<NullCommand>();
    }

}
