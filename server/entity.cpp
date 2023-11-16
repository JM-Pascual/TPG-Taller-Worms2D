#include "entity.h"

#include "battlefield.h"

Entity::Entity(Battlefield& battlefield):
        contact_points(0), dead(false), battlefield(battlefield), collided(false) {}

void Entity::start_contact() { contact_points += 1; }

void Entity::end_contact() { contact_points -= 1; }

void Entity::remove_entity() { battlefield.destroy_body(body); }

bool Entity::multiple_contact() {
    // return contact_points == 1;
    if (not collided) {
        collided = true;
        return false;
    }
    return collided;
}
