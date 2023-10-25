#include "client.h"

#include <spdlog/spdlog.h>

#include "SDL2pp/SDL2pp.hh"

#include "cparser.h"

Client::Client(const char* hostname, const char* servname):
        protocol(hostname, servname), recv(this->protocol, game_state_queue), send(this->protocol) {
    recv.start();
    spdlog::get("client")->debug("Iniciando recv cliente");
    send.start();
}

Client::~Client() {
    protocol.close();
    recv.join();
    send.kill();
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
                    send.queueUp(3);
                    send.queueUp(0);
                    SPDLOG_INFO("cero");
                    break;
                case SDLK_d:
                    send.queueUp(3);
                    send.queueUp(1);
                    SPDLOG_INFO("uno");
                    break;
                default:
                    break;
            }
        } else if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_a:
                    break;
                case SDLK_d:
                    break;
                default:
                    break;
            }
        }

        uint8_t x;
        if (game_state_queue.try_pop(x)) {
            std::cout << "x: " << (int)x << std::endl;
        }
    }

    // render
    // repeat
}
