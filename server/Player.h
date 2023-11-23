#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <memory>
#include <vector>

#include <box2d/box2d.h>

#include "../common/const.h"

#include "entity.h"
#include "weapon.h"
#include "worm.h"

class Weapon;
class Battlefield;
class Projectile;
class BroadCaster;

class Player {
private:
    bool ready;
    bool is_playing;
    std::map<WeaponsAndTools, std::unique_ptr<Weapon>> weapons;
    std::unique_ptr<Weapon>* selected_weapon;
    WeaponsAndTools selected_gadget_type;
    uint8_t worm_turn;

    std::vector<std::shared_ptr<Worm>> worms;

    bool allow_multiple_jump;
    bool immortal_worms;

    void spawnWorms(Battlefield& battlefield, const uint8_t worms_quantity, uint8_t& worm_counter);

public:
    Player();

    void destroyAllWormBodies();

    uint8_t calcAvgLife();

    void set_ready();

    void change_weapon(WeaponsAndTools new_weapon);
    std::unique_ptr<AmmoLeft> getWeaponsAmmo();

    void infiniteAmmo();

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
