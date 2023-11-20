#include "entity.h"

#include "battlefield.h"

Entity::Entity(Battlefield& battlefield):
        dead(false), body(nullptr), battlefield(battlefield), collided(false) {}

void Entity::start_contact() {}

void Entity::end_contact() {}

bool Entity::multiple_contact() {
    if (not collided) {
        collided = true;
        return false;
    }
    return collided;
}

void Entity::start_falling() {}
void Entity::recibe_life_modification(const float& life_variation) {}

bool Entity::is_dead() { return dead; }
