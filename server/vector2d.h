#ifndef VECTOR2D_H
#define VECTOR2D_H

class Player;
class Game;

class Vector2D {
private:
    float x;
    float y;

public:
    Vector2D(const float& x, const float& y): x(x), y(y) {}

    friend class Player;
    friend class Game;
};

#endif
