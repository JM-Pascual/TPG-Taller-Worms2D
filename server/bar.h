#ifndef WORMS2D_BAR_H
#define WORMS2D_BAR_H

#include "box2d/box2d.h"

#include "entity.h"


class Battlefield;

class Bar: public Entity {
private:

public:
    explicit Bar(Battlefield& battlefield);

    void collision_reaction() override;

    void applyWindResistance(const float& wind_force) override;
};


#endif  // WORMS2D_BAR_H
