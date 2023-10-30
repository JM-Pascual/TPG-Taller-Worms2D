#include "GameState.h"

PlayerPosition::PlayerPosition(float x, float y): x(x), y(y) {}

GameState::GameState(float x, float y, bool is_walking, bool direction):
        player_position(x, y), is_walking((IsMoving)is_walking), direction((MoveDir)direction) {}
