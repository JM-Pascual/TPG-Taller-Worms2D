#include "client.h"

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>
#include <spdlog/spdlog.h>

#include "../common/GameState.h"

#include "GameActor.h"
#include "TexturesPool.h"
#include "Window.h"

const int DURATION = 1000 / 30;

Client::Client(const char* hostname, const char* servname):
        quit(false),
        protocol(hostname, servname),
        recv(this->protocol, game_state_queue),
        send(this->protocol, this->action_queue),
        kb(this->action_queue, quit) {
    spdlog::get("client")->debug("Iniciando hilo receptor en el cliente");
    recv.start();
    spdlog::get("client")->debug("Iniciando hilo sender en el cliente");
    send.start();
}

void Client::run() {

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    Window window(1280, 720);
    TexturesPool txt_pool(window.get_renderer());

    std::unordered_map<size_t, std::shared_ptr<GameActor>> actors;
    std::unordered_map<size_t, std::shared_ptr<GameActor>> proyectiles;

    Animation water_animation(txt_pool.get_texture(Actors::WATER), 11, 3);

    kb.start();

    int loop_start_time = SDL_GetTicks();

    while (!quit) {
        window.clear_textures();

        window.render_stage(txt_pool);

        std::shared_ptr<GameState> raw_state = nullptr;

        for (int j = 0; j < 5; j++){
            if (game_state_queue.try_pop(raw_state)) {
                if (raw_state->tag == GameStateTag::PLAYER_COUNT) {
                    uint8_t players_quantity =
                            std::dynamic_pointer_cast<PlayerCount>(raw_state)->quantity;
                    for (size_t i = 0; i < players_quantity; i++) {
                        while (not game_state_queue.try_pop(raw_state)) {}
                        if (actors.count(i) == 0) {
                            actors.insert({i, std::make_shared<Worm>(raw_state, txt_pool)});
                        } else {
                            actors.at(i)->update(raw_state, loop_start_time);
                        }
                        //actors.at(i)->render(window.get_renderer());
                    }
                    //Recibo el gamestate de los proyectiles y los guardo para renderizarlos
                } else if (raw_state->tag == GameStateTag::PROJECTILE_COUNT) {
                    uint8_t proyectiles_quantity =
                            std::dynamic_pointer_cast<ProyectileCount>(raw_state)->quantity;
                    for (size_t i = 0; i < proyectiles_quantity; i++) {
                        while (not game_state_queue.try_pop(raw_state)) {}
                        if (proyectiles.count(i) == 0) {
                            proyectiles.insert({i, std::make_shared<BazookaProyectile>(raw_state, txt_pool)});
                        } else {
                            proyectiles.at(i)->update(raw_state, loop_start_time);
                        }
                    }

                }
            }
        }

        for (auto & actor : actors){
            actor.second->render(window.get_renderer());
        }

        for (auto & proyectile : proyectiles){
            proyectile.second->render(window.get_renderer());
        }

        water_animation.update();

        for (int i = 0; i < 5; i++){
            water_animation.render((*window.get_renderer()), SDL2pp::Rect(0, 600+i*22, 1280, 40), 1240, 0);
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
    kb.join();
    recv.kill();
    send.kill();

    spdlog::get("client")->debug("Cerrando protocolo del cliente");
    protocol.close();
    spdlog::get("client")->debug("Joineando receptor en el cliente");
    recv.join();
    spdlog::get("client")->debug("Joineando sender en el cliente");
    send.join();
}
