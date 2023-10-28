#ifndef CLIENTS_H
#define CLIENTS_H

#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "../common/queue.h"

#include "command.h"

namespace ServerSide {
class Client;
}

class Game {
private:
    std::mutex m;
    std::mutex m_clean;
    std::map<uint8_t, std::unique_ptr<ServerSide::Client>> clients;
    std::condition_variable can_delete;
    Queue<std::shared_ptr<Command>> queue;

public:
    /*
        Crea la lista de clientes vacia
    */
    Game() = default;
    /*
        Envia el DTO a todos los clientes conectados
    */
    void notifyAllClients(const uint8_t& dto);
    /*

    */
    Queue<std::shared_ptr<Command>>& getQueue();
    /*
        Pushea un cliente a la lista
    */
    void pushClient(std::unique_ptr<ServerSide::Client> client);
    /*
        Elimina los clientes muertos y devuelve un bool dependiendo si elimino alguno
    */
    // bool deleteDeaths();
    /*
        Mata todos los clientes conectados
    */
    void killAll();
    /*
        Se utiliza para notificar a can_delete que hay un cliente disponible para ser eliminado
    */
    void notifyClean();
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
