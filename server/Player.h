#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <memory>
#include <vector>

#include <box2d/box2d.h>

#include "../common/const.h"

#include "entity.h"
#include "gadget.h"
#include "worm.h"

#define INITIAL_LIFE 100

#define TICK_RATE 30
#define WIDTH 0.9f
#define HEIGHT 1.2f

#define ARM_LENGHT ((WIDTH / 2) + 1)

#define POWER_RAISE 1
#define MAX_POWER 10
#define ANGLE_VARIATION (b2_pi / 64)

#define CATEGORY_BITS 0x002

#define INCLINACION_MAX (b2_pi / 2)
#define INCLINACION_MIN (-b2_pi / 2)

class Gadget;
class Battlefield;
class Projectile;
class BroadCaster;

class Player {
private:
    bool ready;
    bool is_playing;
    std::map<WeaponsAndTools, std::unique_ptr<Gadget>> weapons;
    std::unique_ptr<Gadget>* selected_weapon;
    WeaponsAndTools selected_gadget_type;
    uint8_t worm_turn;

    std::vector<std::shared_ptr<Worm>> worms;

    void spawnWorms(Battlefield& battlefield, const uint8_t worms_quantity, uint8_t& worm_counter);

public:
    Player();

    void destroyAllWormBodies();

    uint8_t calcAvgLife();

    void set_ready();

    void change_weapon(WeaponsAndTools new_weapon);
    std::unique_ptr<AmmoLeft> getWeaponsAmmo();

    ~Player() = default;

    friend class Game;
    friend class BroadCaster;
    friend class InfoParser;
    friend class WormHandler;
    friend class TurnHandler;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&);
    Player& operator=(Player&&) = delete;
};

#endif  // PLAYER_H
