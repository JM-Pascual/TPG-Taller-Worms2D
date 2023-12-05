#ifndef ACTORHOLDER_H
#define ACTORHOLDER_H

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include "GameActor.h"

class ActorHolder {
private:
    std::unordered_map<uint8_t, std::shared_ptr<GameActor>> active_actors;
    std::unordered_map<uint8_t, std::pair<std::shared_ptr<States>, std::shared_ptr<GameActor>>>
            inactive_actors;

public:
    ActorHolder() = default;

    bool actor_loaded(const uint8_t& actor_id);

    void add_actor(const uint8_t& actor_id, std::shared_ptr<GameActor> new_actor);

    void update_actor_state(uint8_t actor_id, std::shared_ptr<States>& actor_state);

    void remove_actor(const uint8_t& actor_id, std::shared_ptr<States> final_state);

    void play_actors_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                           AudioPlayer& effects_player);

    void print_actors_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                            TextPrinter& state_printer);

    void delete_inactive_actors();
};


#endif  // ACTORHOLDER_H
