#include "GameState.h"

PlayerState::PlayerState(const float x, const float y, const bool is_walking, const bool is_jumping,
                         const bool is_backflipping, const bool facing_right):
        GameState(GameStateTag::PLAYER),
        pos(x, y),
        is_walking(is_walking),
        is_jumping(is_jumping),
        is_backflipping(is_backflipping),
        facing_right(facing_right){}
