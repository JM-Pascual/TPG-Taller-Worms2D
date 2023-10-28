#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include <memory>

#include "../common/queue.h"
#include "../common/thread.h"

class Dto;

namespace ClientSide {
class Protocol;

class Receiver: public Thread {
private:
    ClientSide::Protocol& protocol;
    Queue<std::unique_ptr<Dto>>& game_stateQ;

public:
    explicit Receiver(ClientSide::Protocol& protocol,
                      Queue<std::unique_ptr<Dto>>& game_state_queue);

    void run() override;
};
}  // namespace ClientSide

#endif
