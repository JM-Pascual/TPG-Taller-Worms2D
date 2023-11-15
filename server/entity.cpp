#include "entity.h"
#include "battlefield.h"

Entity::Entity(Battlefield& battlefield) : collide(false), alive(true), battlefield(battlefield) {}

void Entity::start_contact() {collide = true;}

void Entity::end_contact() {collide = false;}

void Entity::remove_entity() {
    battlefield.destroy_body(body);
}
