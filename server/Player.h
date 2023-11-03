#ifndef PLAYER_H
#define PLAYER_H

#include <memory>

#include "../common/const.h"
#include "box2d/box2d.h"

#define PPM 33.33f // pixel per meter ratio.
#define PIXEL_WIDTH 30
#define PIXEL_HEIGHT 40
class Game;

class Player {
private:
    b2Body* worm; //En este caso lo que quiero tener es toda la información del worm cargada y los dos vectores de abajo vuelan
    bool facing_right;
    bool is_moving;

public:
    explicit Player(std::unique_ptr<b2World>& world);

    friend class Game;
};

#endif  // PLAYER_H
