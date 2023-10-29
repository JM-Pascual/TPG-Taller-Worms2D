#include "GameState.h"

GameState::GameState(float x, float y, bool is_walking, MoveDir direction) :
        player_position(x, y), is_walking(is_walking), direction(direction) {}
