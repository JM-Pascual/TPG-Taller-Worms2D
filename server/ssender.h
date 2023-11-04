#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include <memory>

#include "../common/GameState.h"
#include "../common/queue.h"
#include "../common/thread.h"

class GameLoop;

namespace ServerSide {
class Protocol;

class Sender: public Thread {
private:
    ServerSide::Protocol& protocol;
    Queue<std::shared_ptr<GameState>>& game_states;

public:
    explicit Sender(ServerSide::Protocol& protocol, Queue<std::shared_ptr<GameState>>& game_states);
    // Corre el sender esperando que la event_queue tenga un elemento para poder enviar
    //  a traves del protocolo
    void run() override;

    // Debido al uso del heap no se puede copiar ni mover el loop
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    Sender(Sender&&) = delete;
    Sender& operator=(Sender&&) = delete;
};
}  // namespace ServerSide

#endif
