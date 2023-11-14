#include "entity.h"

Entity::Entity() : collide(false), end_life(false) {}

void Entity::start_contact() {collide = true;}

void Entity::end_contact() {collide = false;}
