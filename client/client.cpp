#include "client.h"

#include <spdlog/spdlog.h>

#include "../common/dto.h"
#include "SDL2pp/SDL2pp.hh"

#include "Action.h"
#include "cparser.h"

Client::Client(const char* hostname, const char* servname):
        protocol(hostname, servname),
        recv(this->protocol, game_state_queue),
        send(this->protocol, this->commands_queue) {
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
                    this->commands_queue.push(
                            std::make_unique<MoveDto>(IsMoving::YES, MoveDir::LEFT));
                    break;
                case SDLK_d:
                    this->commands_queue.push(
                            std::make_unique<MoveDto>(IsMoving::YES, MoveDir::RIGHT));
                    break;
                case SDLK_c:
                    this->commands_queue.push(std::make_unique<CreateDto>());
                    break;
                default:
                    break;
            }

        } else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_a:
                    this->commands_queue.push(
                            std::make_unique<MoveDto>(IsMoving::NO, MoveDir::LEFT));
                    break;
                case SDLK_d:
                    this->commands_queue.push(
                            std::make_unique<MoveDto>(IsMoving::NO, MoveDir::RIGHT));
                    break;
                default:
                    break;
            }
        }

        // uint8_t x;
        // if (game_state_queue.try_pop(x)) {
        //     std::cout << "x: " << (int)x << std::endl;
        // }
    }

    // render
    // repeat
}
