#ifndef CLIENT_H
#define CLIENT_H

#include <atomic>
#include <memory>

#include "audio_player.h"
#include "camera.h"
#include "cprotocol.h"
#include "creceiver.h"
#include "csender.h"
#include "inputHandler.h"

class Action;
class States;

class Client {

private:
    std::atomic<bool> quit;
    std::atomic<bool> my_turn;
    std::atomic<bool> runned;
    ClientSide::Protocol protocol;
    ClientSide::Receiver recv;
    ClientSide::Sender send;
    Camera camera;
    IHandler input;
    Queue<std::shared_ptr<States>> game_state_queue;
    Queue<std::shared_ptr<States>> lobby_state_queue;
    Queue<std::shared_ptr<Action>> action_queue;

public:
    /*
        Construye el cliente con su protocolo
    */
    explicit Client(const char* hostname, const char* servname);
    /*
        Corre el cliente
    */
    void run();

    ~Client();

    friend class MainWindow;
    friend class GameFrame;
};


#endif
