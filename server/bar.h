#ifndef WORMS2D_BAR_H
#define WORMS2D_BAR_H

#include "../common/config.h"
#include "box2d/box2d.h"

#include "entity.h"

#define BAR_WIDTH_SHORT 6.0f
#define BAR_WIDTH_LONG 12.0f
#define BAR_HEIGHT 0.8f

//Resolver estas contantes en el YAML


class Battlefield;

class Bar: public Entity {
public:
    explicit Bar(Battlefield& battlefield, float x, float y, float angle, bool is_long);

    void collision_reaction() override;

    void applyWindResistance(const float& wind_force) override;
};


#endif  // WORMS2D_BAR_H
