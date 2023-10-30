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
    spdlog::get("client")->debug("Receptor iniciado con exito");
    spdlog::get("client")->debug("Iniciando hilo sender en el cliente");
    send.start();
    spdlog::get("client")->debug("Sender iniciado con exito");
}

Client::~Client() {
    spdlog::get("client")->debug("Cerrando protocolo del cliente");
    protocol.close();
    spdlog::get("client")->debug("Protocolo cerrado con exito");
    spdlog::get("client")->debug("Joineando receptor en el cliente");
    recv.join();
    spdlog::get("client")->debug("Joineando sender en el cliente");
    send.stop();
    send.join();
}

void Client::run() {
    SDL2pp::SDL sdl(SDL_INIT_VIDEO);

    SDL2pp::Window window("SDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,
                          SDL_WINDOW_RESIZABLE);

    SDL_Event e;
    bool quit = false;
    bool mov_press = false;
    while (!quit) {
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT) {
            quit = true;

        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {

                case SDLK_ESCAPE:
                    quit = true;
                    break;

                case SDLK_a:
                    if (not mov_press) {
                        this->action_queue.push(std::make_shared<StartMoving>(MoveDir::LEFT));
                        mov_press = true;
                    }
                    break;

                case SDLK_d:
                    if (not mov_press) {
                        this->action_queue.push(std::make_shared<StartMoving>(MoveDir::RIGHT));
                        mov_press = true;
                    }
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
                    mov_press = false;
                    break;

                case SDLK_d:
                    this->action_queue.push(std::make_shared<StopMoving>());
                    mov_press = false;
                    break;

                default:
                    break;
            }
        }

        std::shared_ptr<GameState> z = nullptr;
        if (game_state_queue.try_pop(z) && z != nullptr) {
            std::cout << "z: " << float(z->player_position.x) << std::endl;
        }
    }

    // render
    // repeat
}
