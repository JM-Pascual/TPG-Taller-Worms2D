#ifndef WORMS2D_BAR_H
#define WORMS2D_BAR_H

#include "../common/config.h"
#include "box2d/box2d.h"

#include "entity.h"

#define BAR_X Config::yamlNode["bar_x"].as<float>()
#define BAR_Y Config::yamlNode["bar_y"].as<float>()


class Battlefield;

class Bar: public Entity {
public:
    explicit Bar(Battlefield& battlefield);

    void collision_reaction() override;

    void applyWindResistance(const float& wind_force) override;
};


#endif  // WORMS2D_BAR_H
