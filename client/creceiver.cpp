#include "creceiver.h"

#include <spdlog/spdlog.h>

#include "../common/States.h"
#include "../common/liberror.h"

#include "Action.h"
#include "cparser.h"
#include "cprotocol.h"

ClientSide::Receiver::Receiver(ClientSide::Protocol& protocol,
                               Queue<std::shared_ptr<States>>& game_state_queue,
                               Queue<std::shared_ptr<States>>& lobby_state_queue):
        Thread(),
        protocol(protocol),
        game_stateQ(game_state_queue),
        lobby_stateQ(lobby_state_queue) {}

void ClientSide::Receiver::run() {
    do {
        try {
            ClientSide::Parser::filterStates(game_stateQ, lobby_stateQ, protocol.recvStates());

        } catch (const ClosedQueue& e) {
            if (_keep_running) {
                spdlog::get("client")->error("Se cerro la game_state_queue del receiver: {:s}",
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

void ClientSide::Receiver::kill() {
    this->stop();
    this->game_stateQ.close();
}
