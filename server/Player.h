#ifndef PLAYER_H
#define PLAYER_H

#include "../common/const.h"

#include "../common/vector2d.h"

class Game;

class Player {
private:
    Vector2D position;
    Vector2D velocity;
    bool facing_right;

public:
    Player();
    Player(float initial_x, float initial_y);

    friend class Game;
};

#endif  // PLAYER_H
