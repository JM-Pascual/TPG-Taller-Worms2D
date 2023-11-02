#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <memory>

#include "../common/queue.h"
#include "../common/thread.h"

class GameState;

namespace ClientSide {
class Protocol;

class Receiver: public Thread {
private:
    ClientSide::Protocol& protocol;
    Queue<std::shared_ptr<GameState>>& game_stateQ;

public:
    explicit Receiver(ClientSide::Protocol& protocol,
                      Queue<std::shared_ptr<GameState>>& game_state_queue);

    void run() override;
};
}  // namespace ClientSide

#endif