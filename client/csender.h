#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <memory>

#include <stdint.h>

#include "../common/queue.h"
#include "../common/thread.h"

class Action;

namespace ClientSide {
class Protocol;

class Sender: public Thread {
private:
    ClientSide::Protocol& protocol;
    Queue<std::shared_ptr<Action>>& action_queue;

public:
    explicit Sender(ClientSide::Protocol& protocol, Queue<std::shared_ptr<Action>>& action_queue);
    /*
        Corre el sender esperando que la action_queue tenga un elemento para poder enviar a traves
       del protocolo
    */
    void run() override;
    /*
        No tiene sentido ni copiar ni mover el sender
    */
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    Sender(Sender&&) = delete;
    Sender& operator=(Sender&&) = delete;
};
}  // namespace ClientSide

#endif
