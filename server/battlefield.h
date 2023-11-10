
#ifndef WORMS2D_BATTLEFIELD_H
#define WORMS2D_BATTLEFIELD_H

#include <memory>
#include <vector>
#include "box2d/box2d.h"
#include "proyectile.h"

#define X_GRAVITY 0.0f
#define Y_GRAVITY (-10.0f)

#define TIME_STEP (1.0f / 60.0f)
#define VELOCITY_ITERATIONS  (int32) 6
#define POSITION_ITERATIONS  (int32) 2


class Battlefield {
private:
    b2Vec2 gravity;
    std::unique_ptr<b2World> world;
    b2Body* bar;
    std::vector<std::shared_ptr<Proyectile>> proyectile;

    void create_battlefield();

public:
    Battlefield();
    b2Body* add_body(b2BodyDef bodyDef);
    void add_proyectile(std::shared_ptr<Proyectile> proyectile_);
    void step();

    friend class Game;
};

#endif //WORMS2D_BATTLEFIELD_H
