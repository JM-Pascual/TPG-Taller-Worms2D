#ifndef WORMS2D_BAR_H
#define WORMS2D_BAR_H

#include "entity.h"
#include "box2d/box2d.h"


class Battlefield;

class Bar : public Entity{
public:
    explicit Bar(Battlefield& battlefield);
    bool still_alive() override;
    void execute_collision_reaction() override;
};


#endif //WORMS2D_BAR_H
