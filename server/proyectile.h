#ifndef WORMS2D_PROYECTILE_H
#define WORMS2D_PROYECTILE_H


#include <box2d/b2_body.h>
#include <memory>
#include "../common/const.h"
#include "../common/GameState.h"
#include "battlefield.h"

class Battlefield;

class Projectile {
private:
    b2Body* projectile;
    WeaponsAndTools type;
    bool impacted;

public:
    //explicit Projectile (Battlefield& battlefield, b2Vec2 position, float angle, WeaponsAndTools type);
    Projectile (Battlefield& battlefield, b2Vec2 position, float angle, WeaponsAndTools type);

    void set_power(b2Vec2 power);
    std::shared_ptr<ProyectileState> upload_state();
};


#endif //WORMS2D_PROYECTILE_H
