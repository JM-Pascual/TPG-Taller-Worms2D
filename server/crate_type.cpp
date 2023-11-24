#include "crate_type.h"

#include <random>

#include "battlefield.h"
#include "entity.h"
#include "query_callback.h"


FirstAid::FirstAid() {
    auto rng = std::mt19937(std::random_device{}());
    auto random =
            std::uniform_real_distribution<uint8_t>(MIN_HEALTH_FIRST_AID, MAX_HEALTH_FIRST_AID);

    health_quantity = random(rng);
}

void FirstAid::collision_reaction(b2Body*& crate_body, Battlefield& battlefield) {
    Query_callback queryCallback;
    b2AABB aabb;
    aabb.lowerBound = crate_body->GetPosition() - b2Vec2(CRATE_LENGTH / 2, CRATE_LENGTH / 2);
    aabb.upperBound = crate_body->GetPosition() + b2Vec2(CRATE_LENGTH / 2, CRATE_LENGTH / 2);
    battlefield.add_query_AABB(&queryCallback, aabb);

    // check which of these bodies have their center of mass within the blast radius
    for (int i = 0; i < queryCallback.found_bodies_size(); i++) {
        b2Body* body_ = queryCallback.found_bodie_at(i);

        reinterpret_cast<Entity*>(body_->GetUserData().pointer)
                ->recibe_life_modification(health_quantity);
    }
}

AmmoBox::AmmoBox() {
    auto rng = std::mt19937(std::random_device{}());
    auto random = std::uniform_real_distribution<uint8_t>(MIN_AMMO_AMMO_BOX, MAX_AMMO_AMMO_BOX);

    ammo_quantity = random(rng);
}

void AmmoBox::collision_reaction(b2Body*& crate_body, Battlefield& battlefield) {
    Query_callback queryCallback;
    b2AABB aabb;
    aabb.lowerBound = crate_body->GetPosition() - b2Vec2(CRATE_LENGTH / 2, CRATE_LENGTH / 2);
    aabb.upperBound = crate_body->GetPosition() + b2Vec2(CRATE_LENGTH / 2, CRATE_LENGTH / 2);
    battlefield.add_query_AABB(&queryCallback, aabb);

    // check which of these bodies have their center of mass within the blast radius
    for (int i = 0; i < queryCallback.found_bodies_size(); i++) {
        b2Body* body_ = queryCallback.found_bodie_at(i);

        reinterpret_cast<Entity*>(body_->GetUserData().pointer)->reloadAmmo(ammo_quantity);
    }
}

Trap::Trap() {
    auto rng = std::mt19937(std::random_device{}());
    auto random = std::uniform_real_distribution<uint8_t>(MIN_DAMAGE_TRAP, MAX_DAMAGE_TRAP);

    epicenter_dmg = random(rng);
}

void Trap::collision_reaction(b2Body*& crate_body, Battlefield& battlefield) {
    Query_callback queryCallback;
    b2AABB aabb;
    aabb.lowerBound = crate_body->GetPosition() - b2Vec2(CRATE_LENGTH * 2, CRATE_LENGTH * 2);
    aabb.upperBound = crate_body->GetPosition() + b2Vec2(CRATE_LENGTH * 2, CRATE_LENGTH * 2);
    battlefield.add_query_AABB(&queryCallback, aabb);

    // check which of these bodies have their center of mass within the blast radius
    for (int i = 0; i < queryCallback.found_bodies_size(); i++) {
        b2Body* body_ = queryCallback.found_bodie_at(i);

        reinterpret_cast<Entity*>(body_->GetUserData().pointer)
                ->recibe_life_modification(-epicenter_dmg);
    }
}
