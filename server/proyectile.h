#ifndef WORMS2D_PROYECTILE_H
#define WORMS2D_PROYECTILE_H


#include <memory>

#include <box2d/b2_body.h>

#include "../common/States.h"
#include "../common/const.h"
#include "entity.h"

class Battlefield;

class Projectile : public Entity{
private:
    b2Body* projectile;
    WeaponsAndTools type;

public:
    const GameEntity entity;

    explicit Projectile(Battlefield& battlefield, b2Vec2 position, WeaponsAndTools type,
                        GameEntity entity);

    void set_power(b2Vec2 power);
    std::shared_ptr<ProjectileStateG> get_proyectile_state();
    ~Projectile() = default;
};


#endif  // WORMS2D_PROYECTILE_H
