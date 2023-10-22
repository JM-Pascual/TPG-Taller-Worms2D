#include "client.h"

#include "SDL2pp/SDL2pp.hh"

#include "cparser.h"

Client::Client(const char* hostname, const char* servname):
        recv(&this->protocol), send(&this->protocol), protocol(hostname, servname) {
    recv.start();
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
                    send.queueUp(0);
                    break;
                case SDLK_d:
                    send.queueUp(1);
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
    }
}
