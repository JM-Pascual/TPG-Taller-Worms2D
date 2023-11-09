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

    ~PlayerCount() override = default;
};

class PlayerState: public GameState {
public:
    const b2Vec2 pos;
    const bool is_walking;
    const bool is_jumping;
    const bool is_backflipping;
    const bool facing_right;

    explicit PlayerState(float x, float y, bool is_walking, bool is_jumping,
                         bool is_backflipping, bool facing_right);

    ~PlayerState() override = default;
};

class BattlefieldState: public GameState {};

class ProyectileState: public GameState {};

#endif  // GAMESTATE_H
