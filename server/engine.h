
#ifndef WORMS2D_ENGINE_H
#define WORMS2D_ENGINE_H

#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "box2d/box2d.h"

#include "contact_listener.h"

#define X_GRAVITY 0.0f
#define Y_GRAVITY (-16.5f)

#define TIME_STEP (1.0f / 60.0f)
#define VELOCITY_ITERATIONS (int32)6
#define POSITION_ITERATIONS (int32)2

#define MIN_WIND (-7.0f)
#define MAX_WIND 7.0f

class Projectile;

class Engine {
private:
    b2Vec2 gravity;
    std::unique_ptr<b2World> world;
    Contact_listener* listener;

    float wind_force;

    std::uniform_real_distribution<float> random_distribution;
    std::mt19937 rng;

    void create_battlefield();

    void applyWindForce();

public:
    Engine();
    b2Body* add_body(b2BodyDef& bodyDef);
    void add_query_AABB(b2QueryCallback* callback, const b2AABB& aabb);
    void step();
    void destroy_body(b2Body* bodyDef);
    void destroy_dead_entities();
    void clean_dead_entities();

    void newWindForce(const bool& no_wind_cheat_activated);

    friend class InfoParser;

    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;
};

#endif  // WORMS2D_BATTLEFIELD_H
