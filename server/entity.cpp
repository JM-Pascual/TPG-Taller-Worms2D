#include "entity.h"
#include "battlefield.h"

Entity::Entity() : collide(false), alive(true) {}

void Entity::start_contact() {collide = true;}

void Entity::end_contact() {collide = false;}

void Entity::remove_entity(Battlefield* battlefield) {
    battlefield->destroy_body(body);
}
