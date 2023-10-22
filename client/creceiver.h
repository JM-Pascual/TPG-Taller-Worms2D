#ifndef CLIENT_RECEIVER_H
#define CLIENT_RECEIVER_H

#include "../common/queue.h"
#include "../common/thread.h"

namespace ClientSide {
class Protocol;

class Receiver: public Thread {
private:
    ClientSide::Protocol* protocol;
    Queue<uint8_t> queue;

public:
    explicit Receiver(ClientSide::Protocol* protocol);

    void run() override;
};
}  // namespace ClientSide

#endif
