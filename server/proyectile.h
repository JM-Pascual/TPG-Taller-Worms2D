#ifndef WORMS2D_PROYECTILE_H
#define WORMS2D_PROYECTILE_H


#include <box2d/b2_body.h>
#include <memory>
#include "../common/const.h"
#include "../common/GameState.h"

class Proyectile {
private:
    b2Body* proyectile;
    WeaponsAndTools type;
    bool impacted;

public:
    Proyectile(b2Body* proyectile,WeaponsAndTools type);

    std::shared_ptr<ProyectileState> get_proyectile_state();
};


#endif //WORMS2D_PROYECTILE_H
