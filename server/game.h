#ifndef CLIENTS_H
#define CLIENTS_H

#include <condition_variable>
#include <list>
#include <mutex>
#include <string>

namespace ServerSide {
class Client;
}

class Game {
private:
    std::mutex m;
    std::mutex m_clean;
    std::list<ServerSide::Client*> clients;
    std::condition_variable can_delete;

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
        Pushea un cliente a la lista
    */
    void pushClient(ServerSide::Client* c);
    /*
        Elimina los clientes muertos y devuelve un bool dependiendo si elimino alguno
    */
    bool deleteDeaths();
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
