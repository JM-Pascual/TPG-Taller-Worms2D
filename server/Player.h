#ifndef PLAYER_H
#define PLAYER_H

#include "../common/const.h"

class Game;

class Player {
private:
    float x;
    float y;
    bool is_walking;
    MoveDir direction;
public:
    Player();
    Player(float initial_x, float initial_y);

friend class Game;
};

#endif  //PLAYER_H
