#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>

#include "audio_player.h"
#include "text_printer.h"
#include "camera.h"
#include "cprotocol.h"
#include "creceiver.h"
#include "csender.h"
#include "inputHandler.h"
#include "TexturesPool.h"
#include "Window.h"
#include "ActorHolder.h"

class Action;
class States;

class EventLoop {

private:
    /// thread specific atributes
    std::atomic<bool> quit;
    std::atomic<bool> my_turn;
    std::atomic<bool> runned;
    ClientSide::Protocol protocol;
    ClientSide::Receiver recv;
    ClientSide::Sender send;

    /// Media specific atributes and info for rendering
    Camera camera;
    IHandler input;
    AudioPlayer audio_player;
    uint8_t id_of_active_player;

    /// Holders for actors in the game
    ActorHolder players;
    ActorHolder proyectiles;

    /// Queues for the states and actions
    Queue<std::shared_ptr<States>> game_state_queue;
    Queue<std::shared_ptr<States>> lobby_state_queue;
    Queue<std::shared_ptr<Action>> action_queue;

    void process_game_states(std::chrono::time_point<std::chrono::steady_clock>& turn_start,
                                TexturesPool& txt_pool);

public:
    /*
        Construye el cliente con su protocolo
    */
    explicit EventLoop(const char* hostname, const char* servname);
    /*
        Corre el cliente
    */
    void run();

    ~EventLoop();

    friend class MainWindow;
    friend class GameFrame;
};


#endif
