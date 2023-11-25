#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <vector>

#include <stdint.h>

#include "engine.h"
#include "level_holder.h"

class Projectile;
class States;
class Player;
class WormHandler;
class Crate;

class Battlefield {
private:
    /*
        std::mutex m; No hace falta este lock, ya que el unico hilo que utiliza estos metodos es el
       gameloop
    */
    std::map<uint8_t, std::shared_ptr<Projectile>> projectiles;
    uint8_t projectile_count;

    Engine engine;
    Level_holder level_holder;

    std::vector<std::shared_ptr<Crate>> crates;
    uint8_t crate_count;

    void updateProjectilesTimer();
    void post_action_explosion();

public:
    Battlefield(): projectile_count(0), level_holder(*this), crate_count(0) {}

    std::map<uint8_t, std::shared_ptr<Projectile>>& getProjectiles();

    void destroy_body(b2Body*& body);

    b2Body* add_body(b2BodyDef& bodyDef);

    void add_query_AABB(b2QueryCallback* callback, const b2AABB& aabb);

    void step(WormHandler& worm_handler);

    void newWindForce(const bool& no_wind_cheat_activated);

    void add_projectile(std::shared_ptr<Projectile>& proyectile);

    void remove_collided_projectiles();

    void destroy_dead_entities();

    void createCrate();

    const void clearOpenedCrates();

    const bool noProjectiles();

    ~Battlefield() = default;

    friend class InfoParser;
};


#endif
