#include "csender.h"

#include "Action.h"
#include "cprotocol.h"

ClientSide::Sender::Sender(ClientSide::Protocol& protocol,
                           Queue<std::shared_ptr<Action>>& action_queue):
        Thread(), protocol(protocol), action_queue(action_queue) {}

void ClientSide::Sender::run() {
    do {
        try {
            action_queue.pop()->send(protocol);

        } catch (const ClosedQueue& e) {
            break;
        }
    } while (this->_keep_running);
}
