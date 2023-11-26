#ifndef STATES_H
#define STATES_H

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "box2d/b2_math.h"

#include "const.h"

struct AmmoLeft {
public:
    // cppcheck-suppress unusedStructMember
    std::map<WeaponsAndTools, uint8_t> weapon_ammo;
};

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

    explicit GameInfoL(std::string desc, std::string map, const uint8_t& p_count,
                       const uint8_t& id):
            States(StatesTag::INFO_GAME_L),
            description(std::move(desc)),
            map(std::move(map)),
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

// --------------- LEVEL BUILDING STATE ----------------------

struct BarDto {
    BarDto(TerrainActors bar_type, float x, float y, float angle);
    TerrainActors type;
    float x;
    float y;
    const float angle;
};

class LevelStateG: public States {
public:
    uint8_t amount_of_bars;
    std::vector<BarDto> bars;

    explicit LevelStateG(const uint8_t& amount_of_bars, std::vector<BarDto> bars):
            States(StatesTag::LEVEL_BUILD), amount_of_bars(amount_of_bars), bars(std::move(bars)) {}
};

// --------------- TEAM STATE ----------------------

class PlayerStateG: public States {
public:
    const uint8_t id;
    const bool is_playing;
    const uint8_t avg_life;
    const std::unique_ptr<AmmoLeft> gadgets;

    explicit PlayerStateG(const bool& is_playing, const uint8_t& id, const uint8_t& avg_life,
                          std::unique_ptr<AmmoLeft> weapon_ammo):
            States(StatesTag::PLAYER_G),
            id(id),
            is_playing(is_playing),
            avg_life(avg_life),
            gadgets(std::move(weapon_ammo)) {}
};

// --------------- WORM STATES ----------------------

class WormStateG: public States {
public:
    const uint8_t id;
    const b2Vec2 pos;
    const WeaponsAndTools weapon;
    bool on_turn_time;
    const bool is_walking;
    const bool is_jumping;
    const bool is_backflipping;
    const bool facing_right;
    const bool was_hit;

    const float aim_inclination_degrees;
    const bool charging_weapon;
    const float life;
    const bool drown;
    const bool using_tool;


    explicit WormStateG(const uint8_t& id, const float& x, const float& y,
                        const WeaponsAndTools& equipped_weapon, bool on_turn_time,
                        const bool& is_walking, const bool& is_jumping, const bool& is_backflipping,
                        const bool& facing_right, const bool& was_hit,
                        const float& aim_inclination_degrees, const bool& charging_weapon,
                        const float& life, const bool& drown, const bool& using_tool);

    ~WormStateG() override = default;
};

// --------------- BATTLEFIELD STATE ----------------------

class BattlefieldState: public States {
public:
    const uint8_t wind_force;

    explicit BattlefieldState(const uint8_t& wind):
            States(StatesTag::BATTLEFIELD_G), wind_force(wind) {}
};

class ProjectileStateG: public States {
public:
    const uint8_t id;
    const b2Vec2 pos;
    const WeaponsAndTools type;
    const bool impacted;
    const float angle;

    explicit ProjectileStateG(const uint8_t& id, const float& x, const float& y,
                              const WeaponsAndTools& type, const bool& impacted,
                              const float& angle);

    ~ProjectileStateG() override = default;
};

class PlayerTurn: public States {
public:
    const uint8_t is_your_turn;

    explicit PlayerTurn(const bool& is_your_turn):
            States(StatesTag::PLAYER_TURN), is_your_turn(is_your_turn) {}
};

// --------------- COUNT STATES ----------------------

class CountState: public States {
public:
    const uint8_t quantity;

    explicit CountState(const StatesTag& tag, const uint8_t& quantity):
            States(tag), quantity(quantity) {}

    ~CountState() override = default;
};

class GamesCountL: public CountState {
public:
    explicit GamesCountL(const uint8_t& quantity): CountState(StatesTag::GAMES_COUNT_L, quantity) {}

    ~GamesCountL() override = default;
};

class PlayerCountL: public CountState {
public:
    explicit PlayerCountL(const uint8_t& quantity):
            CountState(StatesTag::PLAYER_COUNT_L, quantity) {}

    ~PlayerCountL() override = default;
};

class ProjectileCount: public CountState {
public:
    explicit ProjectileCount(const uint8_t& quantity):
            CountState(StatesTag::PROJECTILE_COUNT, quantity) {}

    ~ProjectileCount() override = default;
};

class GameNotJoinable: public CountState {
public:
    /*
        Por que 0??, Estos states se envian al intentar unirse. Al momento de unirse debe haber como
        minimo una persona, en caso contrario el juego seria limpiado
    */
    GameNotJoinable(): CountState(StatesTag::GAME_NOT_JOINABLE, 0) {}
    explicit GameNotJoinable(const uint8_t& q): CountState(StatesTag::GAME_NOT_JOINABLE, q) {}
};

class ConnectionError: public CountState {
public:
    ConnectionError(): CountState(StatesTag::CONNECTION_ERROR_STATE, CONNECTION_ERROR) {}
};


#endif  // STATES_H
