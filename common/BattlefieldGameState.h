#ifndef WORMS2D_BATTLEFIELDGAMESTATE_H
#define WORMS2D_BATTLEFIELDGAMESTATE_H

#include <vector>
#include "box2d/b2_math.h"

struct bar{
    b2Vec2 bar;
};

class BattlefieldGameState {
public:
    const b2Vec3 bar;

    explicit BattlefieldGameState(const b2Vec3& bar);
};


#endif //WORMS2D_BATTLEFIELDGAMESTATE_H
