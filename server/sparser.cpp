#include "sparser.h"

#include "../common/const.h"

#include "game_browser.h"
#include "player_action.h"
#include "sprotocol.h"

std::shared_ptr<PlayerAction> ServerSide::Parser::makePlayerAction(const Actions& c,
                                                                   ServerSide::Protocol& protocol) {
    switch (c) {
        case Actions::START_MOVING:
            return std::make_shared<StartMoving>(protocol);

        case Actions::STOP_MOVING:
            return std::make_shared<StopMoving>();

        case Actions::JUMP:
            return std::make_shared<NullCommand>();

        default:
            return std::make_shared<NullCommand>();
    }
}

std::shared_ptr<LobbyAction> ServerSide::Parser::makeLobbyAction(
        const Actions& c, ServerSide::Protocol& protocol, GameBrowser& browser,
        std::atomic<bool>& connected_to_room, uint8_t& game_id,
        Queue<std::shared_ptr<GameState>>& game_state) {

    switch (c) {
        case Actions::CREATE:
            return std::make_shared<Create>(browser, game_id, game_state, connected_to_room);

        case Actions::JOIN:
            protocol.recvGameID(game_id);
            return std::make_shared<Join>(browser, game_id, game_state, connected_to_room);

        default:
            return std::make_shared<NullCommand>();
    }
}
