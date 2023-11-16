#include "entity.h"
#include "battlefield.h"

Entity::Entity(Battlefield& battlefield) : contact_points(0), alive(true), battlefield(battlefield) {}

void Entity::start_contact() {contact_points += 1;}

void Entity::end_contact() {contact_points -= 1;}

void Entity::remove_entity() {
    battlefield.destroy_body(body);
}

bool Entity::firts_contact() {
    return contact_points == 1;
}
