#include "battlefield.h"

#include "Player.h"
#include "proyectile.h"
#include "worm_handler.h"

Battlefield::Battlefield() : projectile_count(0), level_holder(*this) {
    level_holder.add_bar(26.6, 9.5, (M_PI*0.25), true);
    level_holder.add_bar(22.6, 8, 0, true);
    level_holder.add_bar(18.6, 8, 0, true);
    level_holder.add_bar(14.6, 8, 0, true);
    level_holder.add_bar(10.6, 8, 0, true);
    level_holder.add_bar(6.6, 8, 0, true);
    level_holder.add_bar(2.6, 9.5, (M_PI*0.75), true);
}

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

bool Battlefield::noProjectiles() { return projectiles.empty(); }
