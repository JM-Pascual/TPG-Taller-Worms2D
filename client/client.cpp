#include "client.h"

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>
#include <spdlog/spdlog.h>

#include "../common/GameState.h"
#include "../common/vector2d.h"

#include "Action.h"
#include "GameActor.h"
#include "TexturesPool.h"
#include "Window.h"

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

                    case SDLK_LEFT:
                        this->action_queue.push(std::make_shared<StartMoving>(Direction::LEFT));
                        break;

                    case SDLK_RIGHT:
                        this->action_queue.push(std::make_shared<StartMoving>(Direction::RIGHT));
                        break;

                    case SDLK_RETURN:
                        this->action_queue.push(std::make_shared<Jump>(JumpDir::FRONT));
                        break;

                    case SDLK_BACKSPACE:
                        this->action_queue.push(std::make_shared<Jump>(JumpDir::BACK));
                        break;


                    // Fight
                    case SDLK_UP:
                        this->action_queue.push(std::make_shared<ADSAngle>(ADSAngleDir::UP));
                        break;

                    case SDLK_DOWN:
                        this->action_queue.push(std::make_shared<ADSAngle>(ADSAngleDir::DOWN));
                        break;

                    case SDLK_SPACE:
                        this->action_queue.push(std::make_shared<FirePower>());
                        break;

                    case SDLK_1:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::ONE));
                        break;

                    case SDLK_2:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::TWO));
                        break;

                    case SDLK_3:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::THREE));
                        break;

                    case SDLK_4:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::FOUR));
                        break;

                    case SDLK_5:
                        this->action_queue.push(std::make_shared<Delay>(DelayAmount::FIVE));
                        break;

                    case SDLK_F1:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::BAZOOKA));
                        break;

                    case SDLK_F2:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::MORTAR));
                        break;

                    case SDLK_F3:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::GREEN_GRENADE));
                        break;

                    case SDLK_F4:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::RED_GRANADE));
                        break;

                    case SDLK_F5:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::BANANA));
                        break;

                    case SDLK_F6:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::HOLY_GRENADE));
                        break;

                    case SDLK_F7:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::DYNAMITE));
                        break;

                    case SDLK_F8:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::BASEBALL_BAT));
                        break;

                    case SDLK_F9:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::AIR_STRIKE));
                        break;

                    case SDLK_F10:
                        this->action_queue.push(
                                std::make_shared<ChangeGadget>(WeaponsAndTools::TELEPORT));
                        break;

                    // ---------- LOBBY ------------
                    case SDLK_c:
                        this->action_queue.push(std::make_shared<CreateGame>());
                        break;

                    default:
                        break;
                }

            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_LEFT:
                        this->action_queue.push(std::make_shared<StopMoving>());
                        break;

                    case SDLK_RIGHT:
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
