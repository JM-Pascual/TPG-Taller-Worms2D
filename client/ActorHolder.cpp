#include "ActorHolder.h"

bool ActorHolder::actor_loaded(const uint8_t& actor_id) { return (active_actors.count(actor_id) != 0); }

void ActorHolder::add_actor(uint8_t actor_id, std::shared_ptr<GameActor> new_actor) {
    active_actors.insert({actor_id, new_actor});
}

void ActorHolder::update_actor_state(uint8_t actor_id, std::shared_ptr<States>& actor_state) {
    active_actors.at(actor_id)->update(actor_state);
}

void ActorHolder::remove_actor(const uint8_t& actor_id, std::shared_ptr<States> final_state) {
    inactive_actors.insert({actor_id, {final_state, active_actors.at(actor_id)}});
    active_actors.erase(actor_id);
}

void ActorHolder::render_actors(std::shared_ptr<SDL2pp::Renderer>& game_renderer) {
    for (auto& actor: active_actors) {
        actor.second->render(game_renderer);
    }

    for (auto& actor: inactive_actors) {
        actor.second.second->update(actor.second.first);
        actor.second.second->render(game_renderer);
    }
}
