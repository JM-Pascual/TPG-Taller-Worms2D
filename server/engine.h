
#ifndef WORMS2D_ENGINE_H
#define WORMS2D_ENGINE_H

#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "../common/config.h"
#include "box2d/box2d.h"

#include "contact_listener.h"

#define X_GRAVITY Config::yamlNode["gravity_x"].as<float>()
#define Y_GRAVITY Config::yamlNode["gravity_y"].as<float>()

#define TIME_STEP Config::yamlNode["time_step"].as<float>()
#define VELOCITY_ITERATIONS Config::yamlNode["velocity_iterations"].as<int>()
#define POSITION_ITERATIONS Config::yamlNode["position_iterations"].as<int>()

#define MIN_WIND Config::yamlNode["min_wind"].as<float>()
#define MAX_WIND Config::yamlNode["max_wind"].as<float>()

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

    void newWindForce(const bool& no_wind_cheat_activated);

    friend class InfoParser;

    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;
};

#endif  // WORMS2D_BATTLEFIELD_H
