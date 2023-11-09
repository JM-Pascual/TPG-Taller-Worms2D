#ifndef WORMS2D_BATTLEFIELDGAMESTATE_H
#define WORMS2D_BATTLEFIELDGAMESTATE_H

#include <vector>

#include "box2d/b2_math.h"

struct bar {
    b2Vec2 bar;
};

class BattlefieldStates {
public:
    const b2Vec3 bar;

    explicit BattlefieldStates(const b2Vec3& bar);
};


#endif  // WORMS2D_BATTLEFIELDGAMESTATE_H
