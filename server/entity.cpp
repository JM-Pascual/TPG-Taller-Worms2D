#include "entity.h"

Entity::Entity() : collide(false)  {}

void Entity::start_contact() {collide = true;}

void Entity::end_contact() {collide = false;}
