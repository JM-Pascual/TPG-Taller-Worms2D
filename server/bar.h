#ifndef WORMS2D_BAR_H
#define WORMS2D_BAR_H

#include "box2d/box2d.h"

#include "entity.h"


class Battlefield;

class Bar: public Entity {
public:
    explicit Bar(Battlefield& battlefield);

    bool is_dead() override;
    void execute_collision_reaction() override;
};


#endif  // WORMS2D_BAR_H
