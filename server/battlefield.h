#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <list>
#include <map>
#include <memory>
#include <mutex>

#include <stdint.h>

#include "engine.h"
#include "level_holder.h"


class Projectile;
class States;
class Player;

class Battlefield {
private:
    std::mutex m;
    std::map<uint8_t, std::shared_ptr<Projectile>> projectiles;
    uint8_t projectile_count;

    Engine engine;
    Level_holder level_holder;

public:
    Battlefield(): projectile_count(0), level_holder(*this) {}

    void build_state(std::list<std::shared_ptr<States>>& states_list);

    void destroy_body(b2Body*& body);

    b2Body* add_body(b2BodyDef& bodyDef);

    void add_query_AABB(b2QueryCallback* callback, const b2AABB& aabb);

    void step();

    void add_projectile(std::shared_ptr<Projectile>& proyectile);

    void remove_collided_projectiles();

    void destroy_dead_entities();

    ~Battlefield() = default;

    friend class Projectile;
    friend class Bar;
    friend class Player;
};


#endif
