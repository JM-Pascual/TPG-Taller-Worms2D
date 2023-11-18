#include "battlefield.h"

#include <algorithm>

#include "../common/States.h"

#include "Player.h"
#include "proyectile.h"

void Battlefield::build_state(std::list<std::shared_ptr<States>>& states_list) {
    std::lock_guard<std::mutex> l(m);

    states_list.push_back(std::make_shared<ProjectileCountG>(projectiles.size()));

    std::transform(projectiles.begin(), projectiles.end(), std::back_inserter(states_list),
                   [](auto& projectile) {
                       return projectile.second->get_proyectile_state(projectile.first);
                   });
}

void Battlefield::destroy_body(b2Body*& body) { engine.destroy_body(body); }

b2Body* Battlefield::add_body(b2BodyDef& bodyDef) { return engine.add_body(bodyDef); }

void Battlefield::add_query_AABB(b2QueryCallback* callback, const b2AABB& aabb) {
    engine.add_query_AABB(callback, aabb);
}

void Battlefield::step() {
    engine.clean_dead_entities();
    engine.step();
}

void Battlefield::add_projectile(std::shared_ptr<Projectile>& proyectile) {
    std::lock_guard<std::mutex> lock(m);
    projectiles.insert({projectile_count++, proyectile});
}

void Battlefield::remove_collided_projectiles() {
    std::lock_guard<std::mutex> lock(m);

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
