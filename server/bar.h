#ifndef WORMS2D_BAR_H
#define WORMS2D_BAR_H

#include "box2d/box2d.h"

#include "entity.h"


class Engine;

class Bar: public Entity {
public:
    explicit Bar(Engine& battlefield);
    bool is_dead() override;
    void execute_collision_reaction() override;
};


#endif  // WORMS2D_BAR_H
