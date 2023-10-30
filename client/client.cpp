#include "client.h"

#include <spdlog/spdlog.h>

#include "../common/GameState.h"
#include "SDL2pp/SDL2pp.hh"

#include "Action.h"

Client::Client(const char* hostname, const char* servname):
        protocol(hostname, servname),
        recv(this->protocol, game_state_queue),
        send(this->protocol, this->action_queue) {
    spdlog::get("client")->debug("Iniciando hilo receptor en el cliente");
    recv.start();
    spdlog::get("client")->debug("Iniciando hilo sender en el cliente");
    send.start();
}

Client::~Client() {
    spdlog::get("client")->debug("Cerrando protocolo del cliente");
    protocol.close();
    spdlog::get("client")->debug("Joineando receptor en el cliente");
    recv.stop();
    recv.join();
    spdlog::get("client")->debug("Joineando sender en el cliente");
    send.stop();
    send.join();
}

void Client::run() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280,
                          720, SDL_WINDOW_RESIZABLE);

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;

            } else if (e.key.repeat == 0 && e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {

                    case SDLK_ESCAPE:
                        quit = true;
                        break;

                    case SDLK_a:
                        this->action_queue.push(std::make_shared<StartMoving>(MoveDir::LEFT));
                        break;

                    case SDLK_d:
                        this->action_queue.push(std::make_shared<StartMoving>(MoveDir::RIGHT));
                        break;

                    case SDLK_c:
                        this->action_queue.push(std::make_shared<CreateGame>());
                        break;

                    default:
                        break;
                }

            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_a:
                        this->action_queue.push(std::make_shared<StopMoving>());
                        break;

                    case SDLK_d:
                        this->action_queue.push(std::make_shared<StopMoving>());
                        break;

                    default:
                        break;
                }
            }
        }

        std::shared_ptr<GameState> z = nullptr;
        if (game_state_queue.try_pop(z)) {
            std::cout << "z: " << float(z->player_position.x) << std::endl;
        }
    }

    // render
    // repeat
}
