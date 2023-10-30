#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "const.h"


class Vector2D_GS {
public:
    const float x;
    const float y;
    Vector2D_GS(const float& x, const float& y);
};

class GameState {
public:
    const Vector2D_GS player_position;
    const bool is_walking;
    const bool facing_right;

    GameState(const float& x, const float& y, bool is_walking, bool direction);

    ~GameState() = default;
};


#endif  // GAMESTATE_H
