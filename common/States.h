#ifndef STATES_H
#define STATES_H

#include <string>

#include <stdint.h>

#include "box2d/b2_math.h"

#include "const.h"

class States {
public:
    const StatesTag tag;

    explicit States(const StatesTag tag): tag(tag) {}

    virtual ~States() = default;
};

class CountState: public States {
public:
    const uint8_t quantity;

    explicit CountState(const StatesTag tag, const uint8_t quantity):
            States(tag), quantity(quantity) {}

    ~CountState() = default;
};

class GamesCountL: public CountState {
public:
    explicit GamesCountL(const uint8_t quantity): CountState(StatesTag::GAMES_COUNT_L, quantity) {}

    ~GamesCountL() = default;
};

class GameInfoL: public States {
public:
    const std::string description;
    const std::string map;
    const uint8_t player_count;
    const uint8_t game_id;

    explicit GameInfoL(const std::string& desc, const std::string& map, const uint8_t& p_count,
                       const uint8_t& id):
            States(StatesTag::INFO_GAME_L),
            description(desc),
            map(map),
            player_count(p_count),
            game_id(id) {}
};

class PlayerCountL: public CountState {
public:
    explicit PlayerCountL(const uint8_t quantity):
            CountState(StatesTag::PLAYER_COUNT_L, quantity) {}

    ~PlayerCountL() = default;
};

class PlayerStateL: public States {
    const bool ready;

    explicit PlayerStateL(const bool& ready): States(StatesTag::PLAYER_L), ready(ready) {}
};

class PlayerCountG: public CountState {
public:
    explicit PlayerCountG(const uint8_t quantity):
            CountState(StatesTag::PLAYER_COUNT_G, quantity) {}

    ~PlayerCountG() = default;
};

class PlayerStateG: public States {
public:
    const b2Vec2 pos;
    const bool is_walking;
    const bool facing_right;

    explicit PlayerStateG(const float x, const float y, const bool is_walking,
                          const bool facing_right);

    ~PlayerStateG() = default;
};

class BattlefieldState: public States {};

class ProyectileState: public States {};

#endif  // STATES_H
