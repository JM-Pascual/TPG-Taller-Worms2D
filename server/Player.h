#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "../common/const.h"
#include "box2d/box2d.h"
#include "battlefield.h"

#define WIDTH 0.9f
#define HEIGHT 1.2f

class Game;

class Player {
private:
    b2Body* worm; //En este caso lo que quiero tener es toda la información del worm cargada y los dos vectores de abajo vuelan
    bool facing_right;
    bool is_moving;
    bool ready;

public:
    explicit Player(Battlefield& battlefield);

    void set_ready();

    friend class Game;
};

#endif  // PLAYER_H
