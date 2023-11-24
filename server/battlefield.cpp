#include "battlefield.h"

#include <algorithm>

#include "../common/States.h"

#include "Player.h"
#include "crate.h"
#include "proyectile.h"
#include "worm_handler.h"

void Battlefield::updateProjectilesTimer() {
    for (auto& projectile: projectiles) {
        projectile.second->updateTimer();
    }
}


void Battlefield::post_action_explosion() {
    for (auto& projectile: projectiles) {
        projectile.second->second_collision_reaction();
    }
}

std::map<uint8_t, std::shared_ptr<Projectile>>& Battlefield::getProjectiles() {
    return projectiles;
}

void Battlefield::destroy_body(b2Body*& body) { engine.destroy_body(body); }

b2Body* Battlefield::add_body(b2BodyDef& bodyDef) { return engine.add_body(bodyDef); }

void Battlefield::add_query_AABB(b2QueryCallback* callback, const b2AABB& aabb) {
    engine.add_query_AABB(callback, aabb);
}

void Battlefield::step(WormHandler& worm_handler) {
    updateProjectilesTimer();
    engine.clean_dead_entities();
    engine.step();
    post_action_explosion();
    worm_handler.update_physics();
    worm_handler.update_weapon();
}

void Battlefield::newWindForce(const bool& no_wind_cheat_activated) {
    engine.newWindForce(no_wind_cheat_activated);
}

void Battlefield::add_projectile(std::shared_ptr<Projectile>& proyectile) {
    projectiles.insert({projectile_count++, proyectile});
}

void Battlefield::remove_collided_projectiles() {
    auto it = projectiles.cbegin();
    while (it != projectiles.cend()) {
        if (it->second->is_dead()) {
            it = projectiles.erase(it);
            continue;
        }
        ++it;
    }
}

void Battlefield::destroy_dead_entities() { engine.destroy_dead_entities(); }

const bool Battlefield::noProjectiles() { return projectiles.empty(); }

void Battlefield::createCrate() { crates.push_back(std::make_shared<Crate>(*this)); }
