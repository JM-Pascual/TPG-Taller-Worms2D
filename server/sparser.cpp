#include "sparser.h"

#include "../common/const.h"
#include "../common/dto.h"

#include "command.h"
#include "game_browser.h"
#include "sprotocol.h"

std::shared_ptr<Command> ServerSide::Parser::makeGameCommand(const Commands& c,
                                                             ServerSide::Protocol& protocol) {
    switch (c) {
        case Commands::MOVE:
            return std::make_shared<Move>(protocol);

        case Commands::JUMP:
            return std::make_shared<NullCommand>();

        default:
            return std::make_shared<NullCommand>();
    }
}

std::shared_ptr<LobbyCommand> ServerSide::Parser::makeLobbyCommand(
        const Commands& c, ServerSide::Protocol& protocol, GameBrowser& gb,
        std::atomic<bool>& connected_to_room, uint8_t& game_id, Queue<std::unique_ptr<Dto>>& game_state) {

    switch (c) {
        case Commands::CREATE:
            return std::make_shared<Create>(gb, game_id, game_state, connected_to_room);

        case Commands::JOIN:
            protocol.recvGameID(game_id);
            return std::make_shared<Join>(gb, game_id, game_state, connected_to_room);

        default:
            return std::make_shared<NullCommand>();
    }
}
