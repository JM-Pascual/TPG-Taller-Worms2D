#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>

#include "../common/config.h"
#include "../common/thread.h"

#include "ActorHolder.h"
#include "TexturesPool.h"
#include "Window.h"
#include "audio_player.h"
#include "camera.h"
#include "cprotocol.h"
#include "creceiver.h"
#include "csender.h"
#include "inputHandler.h"
#include "text_printer.h"

#define FRAME_DURATION Config::yamlNode["frame_duration"].as<int>()

class Action;
class States;
class CheatMenu;

class EventLoop: public Thread {

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
    std::unique_ptr<CheatMenu>& cheat_menu;

    /// Holders for actors in the game
    ActorHolder players;
    ActorHolder proyectiles;

    /// Queues for the states and actions
    Queue<std::shared_ptr<States>> game_state_queue;
    Queue<std::shared_ptr<States>> lobby_state_queue;
    Queue<std::shared_ptr<Action>> action_queue;

    void process_game_states(std::chrono::time_point<std::chrono::steady_clock>& turn_start,
                             TexturesPool& txt_pool);

    void update_terrain(const std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                        Animation& water_animation);

public:
    /*
        Construye el cliente con su protocolo
    */
    explicit EventLoop(const char* hostname, const char* servname,
                       std::unique_ptr<CheatMenu>& cheat_menu);
    /*
        Corre el cliente
    */
    void run() override;

    ~EventLoop();

    friend class MainWindow;
    friend class GameFrame;
    void update_terrain(std::shared_ptr<SDL2pp::Renderer> ptr);
    friend class CheatMenu;
};

#endif
