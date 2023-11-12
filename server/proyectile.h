#ifndef WORMS2D_PROYECTILE_H
#define WORMS2D_PROYECTILE_H


#include <memory>

#include <box2d/b2_body.h>

#include "../common/States.h"
#include "../common/const.h"

#include "battlefield.h"

class Battlefield;

class Projectile {
private:
    b2Body* projectile;
    WeaponsAndTools type;
    bool impacted;

public:
    const GameEntity entity;

    explicit Projectile(Battlefield& battlefield, b2Vec2 position, WeaponsAndTools type,
                        GameEntity entity);

    void set_power(b2Vec2 power);
    std::shared_ptr<ProjectileStateG> get_proyectile_state();
};


#endif  // WORMS2D_PROYECTILE_H
