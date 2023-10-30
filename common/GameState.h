#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "const.h"

struct PlayerPosition {
    float x;
    float y;

    PlayerPosition(float x, float y);
};

class GameState {
public:
    const PlayerPosition player_position;
    const bool is_walking;
    const bool facing_right;

    GameState(float x, float y, bool is_walking, bool direction);

    ~GameState() = default;
};


#endif  // GAMESTATE_H
