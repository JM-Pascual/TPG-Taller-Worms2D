#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "const.h"
#include "vector2d.h"
#include "box2d/b2_math.h"

class WormGameState {
public:
    const b2Vec2 player_position;
    const bool is_walking;
    const bool facing_right;

    WormGameState(const float& x, const float& y, bool is_walking, bool direction);

    ~WormGameState() = default;
};


#endif  // GAMESTATE_H
