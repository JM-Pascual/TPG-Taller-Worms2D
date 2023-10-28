#ifndef GAME_H
#define GAME_H

#include <list>
#include <memory>
#include <mutex>
#include <string>

#include <stdint.h>

#include "../common/queue.h"
#include "../common/thread.h"

#include "command.h"

namespace ServerSide {
class Client;
}

class Game: public Thread {
private:
    std::mutex m;
    std::list<Queue<uint8_t>&> broadcast_list;
    Queue<std::shared_ptr<Command>> queue;

public:
    uint8_t x;

    /*
        Crea la lista de clientes vacia
    */
    Game();
    /*
        Envia el DTO a todos los clientes conectados
    */
    void broadcast(const uint8_t& dto);
    /*

    */
    Queue<std::shared_ptr<Command>>& getQueue();
    /*

    */
    void run() override;
    /*

    */
    void pushQueue(Queue<uint8_t>& client_game_state);
    /*
        Elimina los clientes muertos y devuelve un bool dependiendo si elimino alguno
    */
    // bool deleteDeaths();
    /*
        Mata todos los clientes conectados
    */
    // void killAll();
    /*
        Libera los recursos de todos los clientes
    */
    ~Game();
    /*
        No queremos ni copiar ni mover el monitor
    */
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
};


#endif
