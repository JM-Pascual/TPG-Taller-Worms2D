#include "client_event_loop.h"

#include "../common/const.h"

#include "cheatmenu.h"

#define MAX_PLAYERS Config::commonNode["max_players"].as<int>()
#define WORMS_QUANTITY Config::commonNode["worms_quantity"].as<int>()

EventLoop::EventLoop(const char* hostname, const char* servname,
                     std::unique_ptr<CheatMenu>& cheat_menu):
        quit(false),
        my_turn(false),
        runned(false),
        mouse_priority(false),
        protocol(hostname, servname),
        recv(this->protocol, game_state_queue, lobby_state_queue, runned),
        send(this->protocol, this->action_queue),
        input(this->action_queue, quit, my_turn, camera, mouse_priority),
        cheat_menu(cheat_menu) {
    spdlog::get("client")->debug("Iniciando hilo receptor en el cliente");
    recv.start();
    spdlog::get("client")->debug("Iniciando hilo sender en el cliente");
    send.start();
    cheat_menu = std::make_unique<CheatMenu>(action_queue);
    cheat_menu->hide();
}

void EventLoop::update_terrain() {
    for (auto& terrain: terrain_elements) {
        terrain->update();
    }
}

void EventLoop::render_terrain(const std::shared_ptr<SDL2pp::Renderer>& game_renderer) {
    for (auto& terrain: terrain_elements) {
        terrain->render(game_renderer);
    }
}

void EventLoop::process_game_states(std::chrono::time_point<std::chrono::steady_clock>& turn_start,
                                    TexturesPool& txt_pool) {
    std::shared_ptr<States> raw_state = nullptr;
    int expected_states = MAX_PLAYERS + WORMS_QUANTITY + 3;  //+ proj_count + crate_count + level
    for (int j = 0; j < expected_states; j++) {
        if (not game_state_queue.try_pop(raw_state)) {
            continue;
        }

        switch (raw_state->tag) {
            case StatesTag::PLAYER_G: {
                continue;
            }

            case StatesTag::CRATE_COUNT:
                expected_states += std::dynamic_pointer_cast<CrateCount>(raw_state)->quantity;
                continue;

            case StatesTag::CRATE: {
                auto state = std::dynamic_pointer_cast<CrateState>(raw_state);
                if (!crates.actor_loaded(state->id)) {
                    switch (state->type) {

                        case _CrateType_::FIRST_AID:
                            crates.add_actor(state->id,
                                             std::make_shared<HealCrate>(state, txt_pool, camera));
                            break;
                        case _CrateType_::AMMO_BOX:
                            crates.add_actor(state->id,
                                             std::make_shared<AmmoCrate>(state, txt_pool, camera));
                            break;
                        case _CrateType_::TRAP:
                            crates.add_actor(state->id,
                                             std::make_shared<TrapCrate>(state, txt_pool, camera));
                            break;
                    }
                } else {
                    if (state->was_opened) {
                        crates.remove_actor(state->id, raw_state);
                    } else {
                        crates.update_actor_state(state->id, raw_state);
                    }
                }
                continue;
            }

            case StatesTag::WORM_G: {
                auto state = std::dynamic_pointer_cast<WormStateG>(raw_state);
                if (!players.actor_loaded(state->id)) {
                    players.add_actor(state->id, std::make_shared<Worm>(state, txt_pool, camera));
                } else {
                    if (state->life == 0.0f) {
                        players.remove_actor(state->id, raw_state);
                    } else {
                        players.update_actor_state(state->id, raw_state);
                    }
                }

                viewWorm(state);
                continue;
            }

            case StatesTag::PROJECTILE_COUNT:
                expected_states += std::dynamic_pointer_cast<ProjectileCount>(raw_state)->quantity;
                continue;

            case StatesTag::PROJECTILE_G: {
                auto state = std::dynamic_pointer_cast<ProjectileStateG>(raw_state);
                if (!proyectiles.actor_loaded(state->id)) {
                    switch (state->type) {
                        case (WeaponsAndTools::BAZOOKA): {
                            proyectiles.add_actor(state->id, std::make_shared<BazookaProjectile>(
                                                                     state, txt_pool, camera));
                            break;
                        }
                        case WeaponsAndTools::MORTAR: {
                            proyectiles.add_actor(state->id, std::make_shared<MortarProjectile>(
                                                                     state, txt_pool, camera));
                            break;
                        }

                        case WeaponsAndTools::GREEN_GRENADE: {
                            proyectiles.add_actor(state->id,
                                                  std::make_shared<GreenGrenadeProjectile>(
                                                          state, txt_pool, camera));
                            break;
                        }
                        case WeaponsAndTools::RED_GRENADE:
                            proyectiles.add_actor(state->id, std::make_shared<RedGrenadeProjectile>(
                                                                     state, txt_pool, camera));
                            break;
                        case WeaponsAndTools::BANANA:
                            proyectiles.add_actor(state->id, std::make_shared<BananaProjectile>(
                                                                     state, txt_pool, camera));
                            break;
                        case WeaponsAndTools::HOLY_GRENADE:
                            break;
                        case WeaponsAndTools::DYNAMITE:
                            proyectiles.add_actor(state->id, std::make_shared<DynamiteProjectile>(
                                                                     state, txt_pool, camera));
                            break;
                        case WeaponsAndTools::MORTAR_FRAGMENT:
                            proyectiles.add_actor(state->id, std::make_shared<MortarFragment>(
                                                                     state, txt_pool, camera));
                            break;
                        case WeaponsAndTools::BASEBALL_BAT:
                            break;
                        case WeaponsAndTools::AIR_STRIKE:
                            break;
                        case WeaponsAndTools::TELEPORT:
                            break;
                    }

                } else {
                    if (state->impacted) {
                        proyectiles.remove_actor(state->id, raw_state);
                    } else {
                        proyectiles.update_actor_state(state->id, raw_state);
                    }
                }
                viewProjectile(state);
                continue;
            }

            case StatesTag::PLAYER_TURN: {
                my_turn = std::dynamic_pointer_cast<PlayerTurn>(raw_state)->is_your_turn;
                turn_start = std::chrono::steady_clock::now();
                continue;
            }

            case StatesTag::LEVEL_BUILD: {
                auto state = std::dynamic_pointer_cast<LevelStateG>(raw_state);

                // Charge all the bars as terrain
                for (auto& bar: state->bars) {
                    if (bar.type == TerrainActors::BAR) {
                        terrain_elements.emplace_back(std::make_unique<ShortBar>(
                                bar.x, bar.y, bar.angle, txt_pool, camera));
                    } else {
                        terrain_elements.emplace_back(std::make_unique<LongBar>(
                                bar.x, bar.y, bar.angle, txt_pool, camera));
                    }
                }

                terrain_elements.emplace_back(std::make_unique<Water>(0, 600, txt_pool, camera));
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

    SDL2pp::SDLTTF ttf;
    TextPrinter state_printer(18, txt_pool);

    audio_player.play_background_music();

    input.start();

    int loop_start_time = SDL_GetTicks();

    std::chrono::duration<float> turn_time{};
    std::chrono::time_point<std::chrono::steady_clock> turn_start;

    while (!quit) {
        window.clear_textures();

        window.render_background(txt_pool);
        process_game_states(turn_start, txt_pool);

        turn_time = std::chrono::steady_clock::now() - turn_start;
        // tiempo restante turno = (uint8_t)(60 - turn_time)

        players.render_actors(window.get_renderer());
        players.print_actors_state(window.get_renderer(), state_printer);
        proyectiles.render_actors(window.get_renderer());
        proyectiles.print_actors_state(window.get_renderer(), state_printer);
        crates.render_actors(window.get_renderer());

        update_terrain();
        render_terrain(window.get_renderer());

        window.present_textures();

        int loop_end_time = SDL_GetTicks();
        int rest_time = FRAME_DURATION - (loop_end_time - loop_start_time);

        if (rest_time < 0) {
            int time_behind = -rest_time;

            rest_time = FRAME_DURATION - time_behind % FRAME_DURATION;

            int lost = time_behind + rest_time;
            loop_start_time += lost;
        }

        SDL_Delay(rest_time);
        loop_start_time += FRAME_DURATION;
    }

    cheat_menu->close();
}

void EventLoop::viewWorm(const std::shared_ptr<WormStateG>& worm) {
    if (camera_priority.priority == Priority::PROJECTILE) {
        return;
    }

    if ((camera_priority.id == worm->id) || (camera_priority.priority == Priority::NONE) ||
        (not players.actor_loaded(camera_priority.id))) {

        camera_priority.priority = Priority::WORM;
        camera_priority.id = worm->id;

        if (worm->on_turn_time && not mouse_priority) {
            camera.fixActor(worm->pos.x, worm->pos.y, 32, 60);
        }


        if (worm->is_backflipping) {
            // audio_player.playAudio("test");
            return;

        } else if (worm->is_jumping) {
            // audio_player.playAudio("test");
            return;

        } else if (worm->is_walking) {
            // audio_player.playAudio("test");
            return;

        } else if (worm->charging_weapon) {
            // audio_player.playAudio("test");
            return;

        } else if (worm->using_tool) {
            // audio_player.playAudio("test");
            return;

        } else if (worm->falling) {
            camera.fixActor(worm->pos.x, worm->pos.y, 32, 60);
            // audio_player.playAudio("test");
            return;
        }

        camera_priority.priority = Priority::NONE;
    }
}

void EventLoop::viewProjectile(const std::shared_ptr<ProjectileStateG>& proj) {
    if (camera_priority.priority == Priority::WORM) {
        return;
    }

    if ((camera_priority.id == proj->id) || (camera_priority.priority == Priority::NONE)) {

        camera_priority.priority = Priority::PROJECTILE;
        camera_priority.id = proj->id;

        if (not proj->impacted) {
            camera.fixActor(proj->pos.x, proj->pos.y, 60, 60);
            // audio_player.playAudio("test");
            return;
        }

        camera_priority.priority = Priority::NONE;
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
