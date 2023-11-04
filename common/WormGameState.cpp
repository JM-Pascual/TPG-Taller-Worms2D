#include "WormGameState.h"

WormGameState::WormGameState(const float& x, const float& y, bool is_walking, bool direction):
        player_position(x, y), is_walking(is_walking), facing_right(direction) {}
