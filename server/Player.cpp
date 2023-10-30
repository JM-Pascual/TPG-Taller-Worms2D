#include "Player.h"

Player::Player(): position(0, 0), velocity(0, 0), facing_right(true) {}

Player::Player(float initial_x, float initial_y):
        position(initial_x, initial_y), velocity(0, 0), facing_right(true) {}
