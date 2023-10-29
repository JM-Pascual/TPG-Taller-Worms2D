#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H

#include <memory>

#include "../common/queue.h"
#include "../common/thread.h"
#include "../common/GameState.h"

class GameLoop;

namespace ServerSide {
class Protocol;

class Sender: public Thread {
private:
    ServerSide::Protocol& protocol;
    Queue<std::shared_ptr<GameState>>& game_states;

    //Cierra la event_queue forzosamente
    void closeQueue();
public:
    explicit Sender(ServerSide::Protocol& protocol, Queue<std::shared_ptr<GameState>>& game_states);
    //Corre el sender esperando que la event_queue tenga un elemento para poder enviar
    // a traves del protocolo
    void run() override;

    void send(std::shared_ptr<GameState> state);

    void kill();

    //Debido al uso del heap no se puede copiar ni mover el loop
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    Sender(Sender&&) = delete;
    Sender& operator=(Sender&&) = delete;
};
}  // namespace ServerSide

#endif
