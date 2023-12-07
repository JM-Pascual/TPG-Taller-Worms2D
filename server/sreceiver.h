    #ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <memory>

#include <stdint.h>

#include "../common/States.h"
#include "../common/queue.h"
#include "../common/thread.h"

class GameBrowser;

namespace ServerSide {
class Protocol;

class Receiver: public Thread {
private:
    ServerSide::Protocol& protocol;
    GameBrowser& browser;
    int16_t room_id;
    Queue<std::shared_ptr<States>>& state_queue;

public:
    const uint8_t& id;

    explicit Receiver(ServerSide::Protocol& protocol, GameBrowser& browser,
                      Queue<std::shared_ptr<States>>& state_queue, const uint8_t& id);

    void run() override;
    /*
        Destructor default ya que no tiene que liberar ningun recurso
    */
    ~Receiver() override = default;
    /*

    */
    Receiver(const Receiver&) = delete;
    Receiver& operator=(const Receiver&) = delete;

    Receiver(Receiver&&) = delete;
    Receiver& operator=(Receiver&&) = delete;
};
}  // namespace ServerSide

#endif
