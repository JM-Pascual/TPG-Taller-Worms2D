#include "creceiver.h"

#include <spdlog/spdlog.h>

#include "../common/GameState.h"
#include "../common/liberror.h"

#include "Action.h"
#include "cprotocol.h"

ClientSide::Receiver::Receiver(ClientSide::Protocol& protocol,
                               Queue<std::shared_ptr<GameState>>& game_state_queue):
        Thread(), protocol(protocol), game_stateQ(game_state_queue) {}

void ClientSide::Receiver::run() {
    do {
        try {
            game_stateQ.push(protocol.recvGameState());

        } catch (const ClosedQueue& e) {
            if (_keep_running) {
                spdlog::get("client")->error("Se cerro la action_queue del receiver: {:s}",
                                             e.what());
            }
            break;

        } catch (const LibError& e) {
            if (_keep_running) {
                spdlog::get("client")->error("Se cerro el socket del protocolo en receiver: {:s}",
                                             e.what());
            }
            break;
        }

    } while (_keep_running);
}
