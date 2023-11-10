#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <stdint.h>

#include "const.h"
#include "box2d/b2_math.h"

class GameState {
public:
    const GameStateTag tag;

    explicit GameState(const GameStateTag tag): tag(tag) {}

    virtual ~GameState() = default;
};

class PlayerCount: public GameState {
public:
    const uint8_t quantity;

    explicit PlayerCount(const uint8_t quantity):
            GameState(GameStateTag::PLAYER_COUNT), quantity(quantity) {}

    ~PlayerCount() = default;
};

class ProyectileCount: public GameState {
public:
    const uint8_t quantity;

    explicit ProyectileCount(const uint8_t quantity):
            GameState(GameStateTag::PROYECTILE_COUNT), quantity(quantity) {}

    ~ProyectileCount() = default;
};

class PlayerState: public GameState {
public:
    const b2Vec2 pos;
    const bool is_walking;
    const bool facing_right;
    //const bool is_jumping;

    explicit PlayerState(const float x, const float y, const bool is_walking, const bool facing_right);

    ~PlayerState() = default;
};

class BattlefieldState: public GameState {

};

class ProyectileState: public GameState {
public:
    const b2Vec2 pos;
    const WeaponsAndTools type;
    const bool impacted;

    explicit ProyectileState(const float x, const float y, const WeaponsAndTools type,const bool impacted);

    ~ProyectileState() = default;
};

#endif  // GAMESTATE_H
