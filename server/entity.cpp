#include "entity.h"

#include "battlefield.h"

Entity::Entity(Battlefield& battlefield): dead(false), battlefield(battlefield), collided(false) {}

void Entity::start_contact() {}

void Entity::end_contact() {}

void Entity::remove_entity() { battlefield.destroy_body(body); }

bool Entity::multiple_contact() {
    if (not collided) {
        collided = true;
        return false;
    }
    return collided;
}

void Entity::start_falling() {}
void Entity::recibe_life_modification(float life_variation) {}
