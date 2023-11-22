#ifndef WORMS2D_PROYECTILE_H
#define WORMS2D_PROYECTILE_H


#include <chrono>
#include <memory>

#include <box2d/b2_body.h>

#include "../common/States.h"
#include "../common/const.h"

#include "entity.h"
#include "query_callback.h"


#define BLAST_RADIUS_BAZOOKA 2
#define BLAST_RADIUS_MORTAR 2
#define BLAST_RADIUS_MORTAR_FRAGMENT 2
#define BLAST_RADIUS_GREEN_GRENADE 2
#define BLAST_RADIUS_BANANA 4
#define BLAST_RADIUS_DYNAMITE 4


#define EPICENTER_DAMAGE_BAZOOKA 50
#define EPICENTER_DAMAGE_MORTAR 50
#define EPICENTER_DAMAGE_MORTAR_FRAGMENT 10
#define EPICENTER_DAMAGE_GREEN_GRENADE 30
#define EPICENTER_DAMAGE_BANANA 70
#define EPICENTER_DAMAGE_DYNAMITE 50


#define FRAGMENTS_AMOUNT 6
#define FRAGMENT_POWER 5


#define DEGTORAD 180/b2_pi


class Battlefield;
class Game;

class Projectile: public Entity {
protected:
    WeaponsAndTools type;
    int blast_radius;
    int epicenter_damage;

    void applyBlastImpulse(b2Body* body_, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);

public:
    Projectile(Battlefield& battlefield, b2Vec2 position, int blast_radius, int epicenter_damage,
               WeaponsAndTools type);

    void set_power(b2Vec2 power);
    std::shared_ptr<ProjectileStateG> get_proyectile_state(const uint8_t& proyectile_id);

    void execute_collision_reaction() override {}

    void applyWindResistence(const float& wind_force) override {}

    virtual void execute_second_collision_reaction() = 0;
    virtual void updateTimer() = 0;

    virtual void collide();

    virtual ~Projectile() = default;
    friend class Game;


};


class Rocket: public Projectile {
private:
    // float wind_effect; //todo tiene que ser random por cada una de las rondas --> queda para
    // implementar despues
public:
    Rocket(Battlefield& battlefield, b2Vec2 position,int blast_radius, int epicenter_damage, WeaponsAndTools type);
    void execute_collision_reaction() override;
    void applyWindResistence(const float& wind_force) override;
    void updateTimer() override {}
    void execute_second_collision_reaction() override{};
    void apply_explosion(b2Vec2 final_impulse) override;
    virtual ~Rocket() = default;
};



class BazookaRocket: public Rocket {
public:
    BazookaRocket(Battlefield& battlefield, b2Vec2 position);
    virtual ~BazookaRocket() = default;
};

class MortarRocket: public Rocket {
private:
    int fragments;
public:
    MortarRocket(Battlefield& battlefield, b2Vec2 position);
    void execute_second_collision_reaction() override;
    virtual ~MortarRocket() = default;
};

class MortarFragment: public Rocket {
private:
public:
    MortarFragment(Battlefield& battlefield, b2Vec2 position,b2Vec2 direction);
    virtual ~MortarFragment() = default;
};




class Grenade: public Projectile {
private:
    float explosion_delay;
    std::chrono::time_point<std::chrono::steady_clock> grenade_timer;

public:
    Grenade(Battlefield& battlefield, b2Vec2 position, uint8_t explosion_delay,
            uint8_t blast_radius, uint8_t epicenter_damage, WeaponsAndTools type);
    void execute_collision_reaction() override;
    void applyWindResistence(const float& wind_force) override;
    void updateTimer() override;
    void execute_second_collision_reaction() override{};
    // bool multiple_contact() override;
    virtual ~Grenade() = default;
};


class Green: public Grenade {
public:
    Green(Battlefield& battlefield, b2Vec2 position, uint8_t explosion_delay);
};

class Banana: public Grenade {
public:
    Banana(Battlefield& battlefield, b2Vec2 position, uint8_t explosion_delay);
};

class Dynamite: public Grenade {
public:
    Dynamite(Battlefield& battlefield, b2Vec2 position, uint8_t explosion_delay);
};


#endif  // WORMS2D_PROYECTILE_H
