#include "battlefield.h"

#include <algorithm>

#include "../common/States.h"

#include "Player.h"
#include "proyectile.h"
#include "worm_handler.h"

std::map<uint8_t, std::shared_ptr<Projectile>>& Battlefield::getProjectiles() {
    return projectiles;
}

void Battlefield::destroy_body(b2Body*& body) { engine.destroy_body(body); }

b2Body* Battlefield::add_body(b2BodyDef& bodyDef) { return engine.add_body(bodyDef); }

void Battlefield::add_query_AABB(b2QueryCallback* callback, const b2AABB& aabb) {
    engine.add_query_AABB(callback, aabb);
}

void Battlefield::step(WormHandler& worm_handler) {
    engine.clean_dead_entities();
    engine.step();
    worm_handler.update_physics();
    worm_handler.update_weapon();
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
