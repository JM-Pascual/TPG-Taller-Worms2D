#ifndef ACTORHOLDER_H
#define ACTORHOLDER_H

#include <unordered_map>
#include <vector>
#include <memory>

#include "GameActor.h"

class ActorHolder {
private:
    std::unordered_map<uint8_t, std::shared_ptr<GameActor>> active_actors;
    std::unordered_map<uint8_t, std::pair<std::shared_ptr<States>,
                                          std::shared_ptr<GameActor>>> inactive_actors;
public:
    ActorHolder() = default;

    bool actor_loaded(const uint8_t& actor_id);

    void add_actor(uint8_t actor_id, std::shared_ptr<GameActor> new_actor);

    void update_actor_state(uint8_t actor_id, std::shared_ptr<States>& actor_state);

    void remove_actor(const uint8_t& actor_id, std::shared_ptr<States> final_state);

    void render_actors(std::shared_ptr<SDL2pp::Renderer>& game_renderer);

    void print_actors_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                            TextPrinter& state_printer);
};


#endif  // ACTORHOLDER_H
