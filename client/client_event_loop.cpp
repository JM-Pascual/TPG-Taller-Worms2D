#include "client_event_loop.h"

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>
#include <spdlog/spdlog.h>

#include "../common/States.h"

const int DURATION = 1000 / 30;


EventLoop::EventLoop(const char* hostname, const char* servname):
        quit(false),
        my_turn(false),
        runned(false),
        protocol(hostname, servname),
        recv(this->protocol, game_state_queue, lobby_state_queue, runned),
        send(this->protocol, this->action_queue),
        input(this->action_queue, quit, my_turn, camera) {
    spdlog::get("client")->debug("Iniciando hilo receptor en el cliente");
    recv.start();
    spdlog::get("client")->debug("Iniciando hilo sender en el cliente");
    send.start();
}

void EventLoop::process_game_states(std::chrono::time_point<std::chrono::steady_clock>& turn_start,
                                    TexturesPool& txt_pool) {
    std::shared_ptr<States> raw_state = nullptr;
    for (int j = 0; j < 10; j++) {
        if (not game_state_queue.try_pop(raw_state)) {
            continue;
        }

        switch (raw_state->tag) {
            case StatesTag::PLAYER_G: {
                continue;
            }

            case StatesTag::WORM_G: {
                auto state = std::dynamic_pointer_cast<WormStateG>(raw_state);
                if (!players.actor_loaded(state->id)) {
                    players.add_actor(state->id, std::make_shared<Worm>(state, txt_pool, camera));
                } else {
                    players.update_actor_state(state->id, raw_state);
                }

                if (state->is_walking) {
                    camera.fixActor(state->pos.x, state->pos.y, 32, 60);
                    audio_player.playAudio("test");
                }
                continue;
            }

            case StatesTag::PROJECTILE_G: {
                auto state = std::dynamic_pointer_cast<ProjectileStateG>(raw_state);
                if (!proyectiles.actor_loaded(state->id)) {
                    proyectiles.add_actor(state->id, std::make_shared<BazookaProjectile>(
                                                             state, txt_pool, camera));
                } else {
                    if (std::dynamic_pointer_cast<ProjectileStateG>(raw_state)->impacted) {
                        proyectiles.remove_actor(state->id, raw_state);
                    } else {
                        proyectiles.update_actor_state(state->id, raw_state);
                    }
                }
                continue;
            }

            case StatesTag::PLAYER_TURN: {
                my_turn = std::dynamic_pointer_cast<PlayerTurn>(raw_state)->is_your_turn;
                turn_start = std::chrono::steady_clock::now();
                continue;
            }

            default:
                break;
        }
    }
}

void EventLoop::run() {
    runned = true;
    Window window(1280, 720);
    TexturesPool txt_pool(window.get_renderer());

    SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    audio_player.play_background_music();

    Animation water_animation(txt_pool.get_actor_texture(Actors::WATER), 11, 3);

    input.start();

    int loop_start_time = SDL_GetTicks();

    std::chrono::duration<float> turn_time;
    std::chrono::time_point<std::chrono::steady_clock> turn_start;

    while (!quit) {
        window.clear_textures();

        window.render_stage(txt_pool, camera);
        process_game_states(turn_start, txt_pool);

        turn_time = std::chrono::steady_clock::now() - turn_start;
        // tiempo restante turno = (uint8_t)(60 - turn_time)

        players.render_actors(window.get_renderer());
        proyectiles.render_actors(window.get_renderer());

        water_animation.update();

        for (int i = 0; i < 5; i++) {
            water_animation.render((*window.get_renderer()),
                                   camera.calcRect(0, 600 + i * 22, 1280, 40), 1240, 0);
        }

        window.present_textures();

        int loop_end_time = SDL_GetTicks();
        int rest_time = DURATION - (loop_end_time - loop_start_time);

        if (rest_time < 0) {
            int time_behind = -rest_time;
            rest_time = DURATION - time_behind % DURATION;
            int lost = time_behind + rest_time;
            loop_start_time += lost;
        }

        SDL_Delay(rest_time);
        loop_start_time += DURATION;
    }
}
EventLoop::~EventLoop() {
    if (runned) {
        input.join();
    }

    recv.kill();
    send.kill();

    spdlog::get("client")->debug("Cerrando protocolo del cliente");
    protocol.close();
    spdlog::get("client")->debug("Joineando receptor en el cliente");
    recv.join();
    spdlog::get("client")->debug("Joineando sender en el cliente");
    send.join();
}
