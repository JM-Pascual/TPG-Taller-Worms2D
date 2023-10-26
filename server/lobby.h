#ifndef LOBBY_H
#define LOBBY_H

#include <atomic>
#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include <stdint.h>

#include "../common/queue.h"

#include "game_browser.h"

namespace Lobby_ {
class Cleaner: public Thread {

private:
    std::atomic<bool> killed;
    Lobby& lobby;

public:
    /*
        Crea el lobby cleaner con una referencia al lobby
    */
    explicit Cleaner(Lobby&);
    /*
        Inicia la ejecucion del cleaner, principalmente va estar esperando que se le notifique que
       puede eliminar un lobby client. Va a intentar popear y si popeo de erase_client lo joineara y
       lo eliminara del mapa. Tener en cuenta que esto unicamente sucede si el cliente se unio a un
       Game.
    */
    void run() override;
    /*
        Coloca killed en true para saber si fue intencionado
    */
    void kill();
    /*
        Destructor default ya que no hay que liberar ningun recurso que no este en stack
    */
    ~Cleaner() override = default;
    /*
     *  No queremos ni copiar ni mover el cleaner
     */
    Cleaner(const Cleaner&) = delete;
    Cleaner& operator=(const Cleaner&) = delete;

    Cleaner(Cleaner&&) = delete;
    Cleaner& operator=(Cleaner&&) = delete;
};
}  // namespace Lobby_

class LobbyClient;

class Lobby {
private:
    std::mutex m;
    std::map<uint8_t, std::unique_ptr<LobbyClient>> waiting_clients;
    Queue<uint8_t> erase_client;

    std::atomic<bool> killed;

    GameBrowser gb;

    Lobby_::Cleaner cleaner;

public:
    /*
        Constructor default, excepto que le pasa una referencia de si mismo al cleaner
    */
    Lobby();
    /*
        Delega la creacion de un Game a GameBrowser, retorna la id de este game creado
    */
    uint8_t createGame();
    /*
        Delega a GameBrowser unir el cliente al Game especificado por game_code, luego pushea la id
        de este LobbyClient a la queue y avisa para que sea eliminado
    */
    void joinGame(const uint8_t& game_code, const uint8_t& client_id);
    /*
        Delega a GameBrowser la generacion de la informacion sobre todos los Game disponibles
    */
    void infoGames(std::vector<std::string>&);
    /*
        Agrega un nuevo LobbyClient al mapa
    */
    void pushLobbyClient(std::unique_ptr<LobbyClient>, uint8_t id);
    /*
        Mata al cleaner, los clientes conectados y todos los Game
    */
    void killAll();
    /*
        Borra un cliente segun la id que popea de erase_client
    */
    void eraseClient();
    /*
        Joinea todos los hilos que restan por joinear (como cleaner o algun cliente que quedo
       pendiente)
    */
    ~Lobby();
    /*
     *  No queremos ni copiar ni mover el lobby
     */
    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

    Lobby(Lobby&&) = delete;
    Lobby& operator=(Lobby&&) = delete;
};


#endif
