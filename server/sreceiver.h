#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <atomic>
#include <memory>

#include <stdint.h>

#include "../common/queue.h"
#include "../common/thread.h"
#include "../common/GameState.h"

class GameBrowser;

namespace ServerSide {
class Protocol;

class Receiver: public Thread {
private:
    ServerSide::Protocol& protocol;
    GameBrowser& browser;
    std::atomic<bool> connected_to_room;
    uint8_t room_id;
    Queue<GameState>& state_queue;
public:
    explicit Receiver(ServerSide::Protocol& protocol, GameBrowser& browser,
                      Queue<GameState>& state_queue);

    void run() override;
    /*
        Termina de forma forzosa el thread
    */
    void kill();
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
