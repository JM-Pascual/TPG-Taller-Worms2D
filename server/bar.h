#ifndef WORMS2D_BAR_H
#define WORMS2D_BAR_H

#include "entity.h"
#include "box2d/box2d.h"


class Battlefield;

class Bar : public Entity{
private:
    b2Body* bar;
public:
    explicit Bar(Battlefield& battlefield);
};


#endif //WORMS2D_BAR_H
