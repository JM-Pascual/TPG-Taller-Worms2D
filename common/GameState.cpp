#include "GameState.h"

PlayerState::PlayerState(const float x, const float y, const bool is_walking,
                         const bool facing_right):
        GameState(GameStateTag::PLAYER),
        pos(x, y),
        is_walking(is_walking),
        facing_right(facing_right){}
        //is_jumping(is_jumping)
