#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <memory>

#include "../common/queue.h"
#include "../common/thread.h"

class States;

namespace ClientSide {
class Protocol;

class Receiver: public Thread {
private:
    ClientSide::Protocol& protocol;
    Queue<std::shared_ptr<States>>& game_stateQ;
    Queue<std::shared_ptr<States>>& lobby_stateQ;

public:
    explicit Receiver(ClientSide::Protocol& protocol,
                      Queue<std::shared_ptr<States>>& game_state_queue,
                      Queue<std::shared_ptr<States>>& lobby_state_queue);

    void run() override;

    void kill();
};
}  // namespace ClientSide

#endif
