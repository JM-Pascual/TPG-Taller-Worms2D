
#ifndef WORMS2D_BATTLEFIELD_H
#define WORMS2D_BATTLEFIELD_H

#include <memory>
#include <vector>
#include <iostream>
#include "box2d/box2d.h"
#include "contact_listener.h"

#define X_GRAVITY 0.0f
#define Y_GRAVITY (-16.5f)

#define TIME_STEP (1.0f / 60.0f)
#define VELOCITY_ITERATIONS  (int32) 6
#define POSITION_ITERATIONS  (int32) 2

class Projectile;

class Battlefield{
private:
    b2Vec2 gravity;
    std::unique_ptr<b2World> world;
    Contact_listener* listener;

    void create_battlefield();

public:
    Battlefield();
    b2Body* add_body(b2BodyDef& bodyDef);
    void add_query_AABB(b2QueryCallback* callback, const b2AABB& aabb);
    void step();
    void destroy_body(b2Body* bodyDef);
    void destroy_dead_entities();
    void clean_dead_entities();

    friend class Game;


};

#endif //WORMS2D_BATTLEFIELD_H
