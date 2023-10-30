#include "GameState.h"

Vector2D_GS::Vector2D_GS(const float& x, const float& y): x(x), y(y) {}

GameState::GameState(const float& x, const float& y, bool is_walking, bool direction):
        player_position(x, y), is_walking(is_walking), facing_right(direction) {}
