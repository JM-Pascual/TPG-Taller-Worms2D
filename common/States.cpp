#include "States.h"

PlayerState::PlayerState(const float x, const float y, const bool is_walking,
                         const bool facing_right):
        States(StatesTag::PLAYER_G),
        pos(x, y),
        is_walking(is_walking),
        facing_right(facing_right) {}
