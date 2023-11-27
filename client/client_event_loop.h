#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <list>
#include <memory>

#include <SDL2pp/SDL2pp.hh>
#include <spdlog/spdlog.h>

#include "../common/config.h"
#include "../common/thread.h"

#include "ActorHolder.h"
#include "GameActor.h"
#include "LevelActors.h"
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
    std::atomic<bool> mouse_priority;
    ClientSide::Protocol protocol;
    ClientSide::Receiver recv;
    ClientSide::Sender send;

    /// Media specific atributes and info for rendering
    Camera camera;
    IHandler input;
    AudioPlayer audio_player;
    std::unique_ptr<CheatMenu>& cheat_menu;

    /// Holders for actors in the game
    std::list<std::unique_ptr<LevelActor>> terrain_elements;
    ActorHolder players;
    ActorHolder proyectiles;
    ActorHolder crates;

    /// Queues for the states and actions
    Queue<std::shared_ptr<States>> game_state_queue;
    Queue<std::shared_ptr<States>> lobby_state_queue;
    Queue<std::shared_ptr<Action>> action_queue;

    CameraPriority camera_priority;

    void process_game_states(std::chrono::time_point<std::chrono::steady_clock>& turn_start,
                             TexturesPool& txt_pool);

    void update_terrain();
    void render_terrain(const std::shared_ptr<SDL2pp::Renderer>& game_renderer);

    void viewWorm(const std::shared_ptr<WormStateG>& worm);

    void viewProjectile(const std::shared_ptr<ProjectileStateG>& proj);

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
    friend class CheatMenu;
};

#endif
