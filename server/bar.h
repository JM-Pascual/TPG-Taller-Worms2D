#ifndef WORMS2D_BAR_H
#define WORMS2D_BAR_H

#include "../common/const.h"
#include "box2d/box2d.h"

#include "entity.h"

#define BAR_WIDTH_SHORT 2.1f  // 1.9f
#define BAR_WIDTH_LONG 4.2f   // 4.0f
#define BAR_HEIGHT 0.7f

// Resolver estas contantes en el YAML

class Battlefield;
class LevelHolder;

class Bar: public Entity {
private:
    float width;
    float angle;
    b2Vec2 get_bar_position();
    TerrainActors get_bar_type() const;

    [[nodiscard]] float get_bar_width() const;
    [[nodiscard]] float get_bar_height() const;

public:
    explicit Bar(Battlefield& battlefield, const float& x, const float& y,
                 const float& inclination_angle, const bool& is_long);

    void collision_reaction(const b2Vec2& normal) override;

    void applyWindResistance(const float& wind_force) override;

    friend class LevelHolder;
};


#endif  // WORMS2D_BAR_H
