#ifndef WORMS2D_PROYECTILE_H
#define WORMS2D_PROYECTILE_H


#include <memory>

#include <box2d/b2_body.h>

#include "../common/States.h"
#include "../common/const.h"

#include "entity.h"
#include "query_callback.h"


/*
 *
 * */


class Battlefield;
class Game;

class Projectile: public Entity {
private:
    WeaponsAndTools type;
    float blast_radius;
    float epicenter_damage;


    void applyBlastImpulse(b2Body* body_, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);

public:
    explicit Projectile(Battlefield& battlefield, b2Vec2 position, WeaponsAndTools type);

    void set_power(b2Vec2 power);
    std::shared_ptr<ProjectileStateG> get_proyectile_state();
    bool is_dead() override;
    void execute_collision_reaction() override;

    ~Projectile() = default;
    friend class Game;

    void collide();
};

/*
class Rocket : public Projectile{
private:
    //float wind_effect; //todo tiene que ser random por cada una de las rondas --> queda para implementar despues
public:
    Rocket(Battlefield& battlefield, b2Vec2 position);
    void execute_collision_reaction() override;
};

class Grenade : public Projectile{
private:
    uint8_t explosion_delay;

public:
    Grenade(Battlefield& battlefield, b2Vec2 position);
    void execute_collision_reaction() override;
};
*/






#endif  // WORMS2D_PROYECTILE_H
