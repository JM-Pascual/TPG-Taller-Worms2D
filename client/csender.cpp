#include "csender.h"

#include "../common/dto.h"

#include "Action.h"
#include "cprotocol.h"

ClientSide::Sender::Sender(ClientSide::Protocol& protocol,
                           Queue<std::unique_ptr<Action>>& commands_queue):
        Thread(), protocol(protocol), commands_queue(commands_queue) {}

void ClientSide::Sender::run() {
    do {
        try {
            commands_queue.pop()->send(protocol);

        } catch (const ClosedQueue& e) {
            break;
        }
    } while (this->_keep_running);
}
