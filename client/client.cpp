#include "client.h"

#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>
#include <spdlog/spdlog.h>

#include "../common/GameState.h"

#include "GameActor.h"
#include "TexturesPool.h"
#include "Window.h"

const int frameDuration = 1000 / 30;

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

void Client::run() {

    SDL2pp::SDL sdl(SDL_INIT_VIDEO);
    Window window(1280, 720);
    TexturesPool txt_pool(window.get_renderer());

    std::unordered_map<size_t, std::shared_ptr<GameActor>> actors;

    Animation water_animation(txt_pool.get_texture(Actors::WATER), 11, 3);

    kb.start();

    int t1 = SDL_GetTicks();

    while (!quit) {
        window.clear_textures();

        window.render_stage(txt_pool);

        std::shared_ptr<GameState> raw_state = nullptr;
        if (game_state_queue.try_pop(raw_state)) {
            if (raw_state->tag == GameStateTag::PLAYER_COUNT) {
                uint8_t players_quantity =
                        std::dynamic_pointer_cast<PlayerCount>(raw_state)->quantity;
                for (size_t i = 0; i < players_quantity; i++) {
                    while (not game_state_queue.try_pop(raw_state)) {}
                    if (actors.count(i) == 0) {
                        actors.insert(
                                {i, std::make_shared<Worm>(raw_state, txt_pool)});
                    } else {
                        actors.at(i)->update(raw_state, t1);
                    }
                    actors.at(i)->render(window.get_renderer());
                }
            }
        }

        water_animation.update();

        for (int i = 0; i < 5; i++){
            water_animation.render((*window.get_renderer()), SDL2pp::Rect(0, 600+i*22, 1280, 40), 1240, 0);
        }

        // Show rendered frame
        window.present_textures();

        int t2 = SDL_GetTicks();
        int rest = frameDuration - (t2 - t1);

        if (rest < 0) {
            int behind = -rest;
            rest = frameDuration - behind % frameDuration;
            int lost = behind + rest;
            t1 += lost;
        }

        SDL_Delay(rest);
        t1 += frameDuration;
    }
}
