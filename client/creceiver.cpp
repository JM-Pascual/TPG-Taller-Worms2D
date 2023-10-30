#include "creceiver.h"

#include "../common/GameState.h"

#include "Action.h"
#include "cprotocol.h"

ClientSide::Receiver::Receiver(ClientSide::Protocol& protocol,
                               Queue<std::shared_ptr<GameState>>& game_state_queue):
        Thread(), protocol(protocol), game_stateQ(game_state_queue) {}

void ClientSide::Receiver::run() {
    do {
        game_stateQ.push(protocol.recvGameState());
    } while (_keep_running);
}
