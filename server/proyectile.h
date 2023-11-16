#ifndef WORMS2D_PROYECTILE_H
#define WORMS2D_PROYECTILE_H


#include <memory>

#include <box2d/b2_body.h>

#include "../common/States.h"
#include "../common/const.h"

#include "entity.h"
#include "query_callback.h"

class Battlefield;

class Projectile: public Entity {
private:
    WeaponsAndTools type;
    float blast_radius;

    void applyBlastImpulse(b2Body* body, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower);

public:
    explicit Projectile(Battlefield& battlefield, b2Vec2 position, WeaponsAndTools type);

    void set_power(b2Vec2 power);
    std::shared_ptr<ProjectileStateG> get_proyectile_state();
    bool is_dead() override;
    void execute_collision_reaction() override;

    ~Projectile() = default;
};


#endif  // WORMS2D_PROYECTILE_H
