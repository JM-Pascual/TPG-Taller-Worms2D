#include "Player.h"

Player::Player(): x(0), y(0), is_walking(false), facing_right(true) {}

Player::Player(float initial_x, float initial_y):
        x(initial_x), y(initial_y), is_walking(false), facing_right(true) {}
