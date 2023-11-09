#ifndef STATES_H
#define STATES_H

#include <stdint.h>

#include "box2d/b2_math.h"

#include "const.h"

class States {
public:
    const StatesTag tag;

    explicit States(const StatesTag tag): tag(tag) {}

    virtual ~States() = default;
};

class PlayerCount: public States {
public:
    const uint8_t quantity;

    explicit PlayerCount(const uint8_t quantity):
            States(StatesTag::PLAYER_COUNT_G), quantity(quantity) {}

    ~PlayerCount() = default;
};

class PlayerState: public States {
public:
    const b2Vec2 pos;
    const bool is_walking;
    const bool facing_right;

    explicit PlayerState(const float x, const float y, const bool is_walking,
                         const bool facing_right);

    ~PlayerState() = default;
};

class BattlefieldState: public States {};

class ProyectileState: public States {};

#endif  // STATES_H
