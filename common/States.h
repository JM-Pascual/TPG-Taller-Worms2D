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


class PlayerStateL: public States {
public:
    const bool ready;
    const uint8_t id;

    explicit PlayerStateL(const bool& ready, const uint8_t& id):
            States(StatesTag::PLAYER_L), ready(ready), id(id) {}
};


class PlayerStateG: public States {
public:
    const b2Vec2 pos;
    const bool is_walking;
    const bool is_jumping;
    const bool is_backflipping;
    const bool facing_right;
    float aim_inclination_degrees;

    explicit PlayerStateG(float x, float y, bool is_walking, bool is_jumping, bool is_backflipping,
                          bool facing_right, float aim_inclination_degrees);

    ~PlayerStateG() override = default;
};

class BattlefieldState: public States {};

class ProjectileStateG: public States {
public:
    const b2Vec2 pos;
    const WeaponsAndTools type;
    const bool impacted;
    const float angle;

    explicit ProjectileStateG(const float x, const float y, const WeaponsAndTools type,
                              const bool impacted, const float angle);

    ~ProjectileStateG() override = default;
};


// --------------- COUNT STATES ----------------------

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

class PlayerCountL: public CountState {
public:
    explicit PlayerCountL(const uint8_t quantity):
            CountState(StatesTag::PLAYER_COUNT_L, quantity) {}

    ~PlayerCountL() = default;
};

class PlayerCountG: public CountState {
public:
    explicit PlayerCountG(const uint8_t quantity):
            CountState(StatesTag::PLAYER_COUNT_G, quantity) {}

    ~PlayerCountG() = default;
};

class ProjectileCountG: public CountState {
public:
    explicit ProjectileCountG(const uint8_t quantity):
            CountState(StatesTag::PROJECTILE_COUNT_G, quantity) {}

    ~ProjectileCountG() = default;
};

class GameNotJoinable: public CountState {
public:
    /*
        Por que 0??, Estos states se envian al intentar unirse. Al momento de unirse debe haber como
        minimo una persona, en caso contrario el juego seria limpiado
    */
    GameNotJoinable(): CountState(StatesTag::GAME_NOT_JOINABLE, 0) {}
    explicit GameNotJoinable(const uint8_t q): CountState(StatesTag::GAME_NOT_JOINABLE, q) {}
};

class ConnectionError: public CountState {
public:
    ConnectionError(): CountState(StatesTag::CONNECTION_ERROR_STATE, CONNECTION_ERROR) {}
};

#endif  // STATES_H
