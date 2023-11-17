#include "client.h"

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>
#include <spdlog/spdlog.h>

#include "../common/States.h"

#include "GameActor.h"
#include "TexturesPool.h"
#include "Window.h"
#include "ActorHolder.h"

const int DURATION = 1000 / 30;


Client::Client(const char* hostname, const char* servname):
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

void Client::run() {
    runned = true;
    SDL2pp::SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    Window window(1280, 720);
    TexturesPool txt_pool(window.get_renderer());
    AudioPlayer audio_player;

    ActorHolder players;
    ActorHolder proyectiles;

    Animation water_animation(txt_pool.get_texture(Actors::WATER), 11, 3);

    input.start();

    int loop_start_time = SDL_GetTicks();

    std::chrono::duration<float> turn_time;
    std::chrono::time_point<std::chrono::steady_clock> turn_start;

    while (!quit) {
        window.clear_textures();

        window.render_stage(txt_pool, camera);

        std::shared_ptr<States> raw_state = nullptr;

        for (int j = 0; j < 5; j++) {
            if (game_state_queue.try_pop(raw_state)) {
                if (raw_state->tag == StatesTag::PLAYER_COUNT_G) {
                    uint8_t players_quantity =
                            std::dynamic_pointer_cast<PlayerCountG>(raw_state)->quantity;
                    for (size_t i = 0; i < players_quantity; i++) {
                        while (not game_state_queue.try_pop(raw_state)) {}
                        auto state = std::dynamic_pointer_cast<PlayerStateG>(raw_state);
                        if (!players.actor_loaded(state->id)) {
                            players.add_actor(
                                    state->id, std::make_shared<Worm>(raw_state, txt_pool, camera)
                            );
                        } else {
                            players.update_actor_state(state->id, raw_state);
                        }

                        auto worm = std::dynamic_pointer_cast<PlayerStateG>(raw_state);
                        if (worm->is_walking) {
                            camera.fixActor(worm->pos.x, worm->pos.y, 32, 60);
                            audio_player.playAudio("test");
                        }
                    }
                    // Recibo el States de los proyectiles y los guardo para renderizarlos
                } else if (raw_state->tag == StatesTag::PROJECTILE_COUNT_G) {
                    uint8_t proyectiles_quantity =
                            std::dynamic_pointer_cast<ProjectileCountG>(raw_state)->quantity;
                    for (size_t i = 0; i < proyectiles_quantity; i++) {
                        while (not game_state_queue.try_pop(raw_state)) {}
                        auto state = std::dynamic_pointer_cast<ProjectileStateG>(raw_state);
                        if (!proyectiles.actor_loaded(state->id)) {
                            proyectiles.add_actor(
                                    state->id,
                                    std::make_shared<BazookaProyectile>(raw_state, txt_pool, camera)
                            );
                        } else {
                            if (std::dynamic_pointer_cast<ProjectileStateG>(raw_state)->impacted){
                                proyectiles.remove_actor(state->id, raw_state);
                            } else{
                                proyectiles.update_actor_state(state->id, raw_state);
                            }
                        }
                    } else if (raw_state->tag == StatesTag::PLAYER_TURN) {
                        // contar tiempo
                        my_turn = std::dynamic_pointer_cast<PlayerTurn>(raw_state)->is_your_turn;
                        turn_start = std::chrono::steady_clock::now();
                    }
                }
            }
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

Client::~Client() {
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
