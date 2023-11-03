#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "const.h"
#include "vector2d.h"
#include "box2d/b2_math.h"

class GameState {
public:
    const b2Vec2 player_position;
    const bool is_walking;
    const bool facing_right;

    GameState(const float& x, const float& y, bool is_walking, bool direction);

    ~GameState() = default;
};


#endif  // GAMESTATE_H
