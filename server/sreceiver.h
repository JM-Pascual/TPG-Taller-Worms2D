#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <atomic>
#include <memory>

#include "../common/thread.h"

class GameBrowser;

namespace ServerSide {
class Protocol;

class Receiver: public Thread {
private:
    ServerSide::Protocol& protocol;
    const GameBrowser& gb;
    std::atomic<bool> joined_game;

public:
    explicit Receiver(ServerSide::Protocol& protocol, const GameBrowser& gb);

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
