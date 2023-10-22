#ifndef CLIENT_SENDER_H
#define CLIENT_SENDER_H

#include <stdint.h>

#include "../common/queue.h"
#include "../common/thread.h"

namespace ClientSide {
class Protocol;

class Sender: public Thread {
private:
    ClientSide::Protocol& protocol;
    Queue<uint8_t> queue;
    /*
        Cierra la queue forzosamente
    */
    void closeQueue();

public:
    explicit Sender(ClientSide::Protocol& protocol);
    /*
        Corre el sender esperando que la queue tenga un elemento para poder enviar a traves del
        protocolo
    */
    void run() override;

    void send(uint8_t o);

    void queueUp(uint8_t o);

    void kill();
    /*
        No tiene sentido ni copiar ni mover el sender ya que al ser un thread lo vamos a utilizar en
        el heap
    */
    Sender(const Sender&) = delete;
    Sender& operator=(const Sender&) = delete;

    Sender(Sender&&) = delete;
    Sender& operator=(Sender&&) = delete;
};
}  // namespace ClientSide

#endif
