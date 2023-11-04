#include "Player.h"

// ToDo Hardocdeado para que los worms aparezcan en la mitad del mapa
Player::Player(): position(0, 360), velocity(0, 0), facing_right(true), ready(false) {}

Player::Player(float initial_x, float initial_y):
        position(initial_x, initial_y), velocity(0, 0), facing_right(true), ready(false) {}

void Player::set_ready() { ready = !ready; }
