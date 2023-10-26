#ifndef SERVER_RECEIVER_H
#define SERVER_RECEIVER_H

#include <memory>

#include "../common/thread.h"

class Game;

namespace ServerSide {
class Protocol;

class Receiver: public Thread {
private:
    ServerSide::Protocol& protocol;
    std::unique_ptr<Game>& game;

public:
    explicit Receiver(ServerSide::Protocol& protocol, std::unique_ptr<Game>& game);

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
