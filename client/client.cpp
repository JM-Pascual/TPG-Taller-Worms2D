#include "client.h"

#include <spdlog/spdlog.h>

#include "../common/GameState.h"
#include "../common/vector2d.h"

#include <SDL2pp/SDL2pp.hh>

#include "Action.h"
#include "Window.h"
#include "GameActor.h"
#include "TexturesPool.h"

const int frameDuration = 1000 / 60;

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
    Window window(1280, 720);
    TexturesPool txt_pool(window.get_renderer());

    std::unordered_map<size_t, std::shared_ptr<GameActor>> actors;

    Animation water_animation(txt_pool.get_texture(Actors::WATER), 12);

    bool quit = false;
    while (!quit) {
        unsigned int loop_start_ticks = SDL_GetTicks();

        SDL_Event e;
        // Polling de events para enviar al sv
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

        window.clear_textures();

        window.render_stage(txt_pool);

        std::shared_ptr<GameState> raw_state = nullptr;
        if (game_state_queue.try_pop(raw_state)) {
            if (actors.empty()) {
                actors.insert({0, std::make_shared<Worm>(raw_state, loop_start_ticks, txt_pool)});
            } else {
                actors.at(0)->update(raw_state, loop_start_ticks);
            }
            actors.at(0)->render(window.get_renderer());
        }

        water_animation.update(loop_start_ticks, false);
        water_animation.render((*window.get_renderer()), SDL2pp::Rect(0, 600, 1280, 40), 1256, 1);

        // Show rendered frame
        window.present_textures();

        unsigned int loop_finish_ticks = SDL_GetTicks();
        unsigned int elapsed_ticks = loop_finish_ticks - loop_start_ticks;

        if (elapsed_ticks < frameDuration) {
            SDL_Delay(frameDuration - elapsed_ticks);
        }
    }
}
