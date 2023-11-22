#include "Player.h"

#include <numeric>
#include <utility>

#include "../common/States.h"

#include "battlefield.h"
#include "engine.h"

// ToDo Hardocdeado para que los worms aparezcan en la mitad del mapa

Player::Player():
        ready(false),
        is_playing(true),
        selected_weapon(nullptr),
        selected_gadget_type(WeaponsAndTools::BAZOOKA),
        worm_turn(0) {
    weapons.insert({WeaponsAndTools::BAZOOKA, std::make_unique<Bazooka>()});
    weapons.insert({WeaponsAndTools::MORTAR, std::make_unique<Mortar>()});
    weapons.insert({WeaponsAndTools::GREEN_GRENADE, std::make_unique<GreenGrenade>()});
    weapons.insert({WeaponsAndTools::RED_GRENADE, std::make_unique<RedGrenade>()});
    weapons.insert({WeaponsAndTools::BANANA, std::make_unique<BananaGrenade>()});
    weapons.insert({WeaponsAndTools::HOLY_GRENADE, std::make_unique<Bazooka>()});
    weapons.insert({WeaponsAndTools::DYNAMITE, std::make_unique<DynamiteGrenade>()});
    weapons.insert({WeaponsAndTools::BASEBALL_BAT, std::make_unique<Bazooka>()});
    weapons.insert({WeaponsAndTools::AIR_STRIKE, std::make_unique<Bazooka>()});
    weapons.insert({WeaponsAndTools::TELEPORT, std::make_unique<Bazooka>()});

    selected_weapon = &weapons.at(WeaponsAndTools::BAZOOKA);
}

uint8_t Player::calcAvgLife() {
    float life_sum =
            std::accumulate(worms.begin(), worms.end(), 0,
                            [](const float& sum, const auto& worm) { return sum + worm->life; });

    return (uint8_t)(life_sum / worms.size());
}

void Player::set_ready() { ready = !ready; }

void Player::spawnWorms(Battlefield& battlefield, const uint8_t worms_quantity,
                        uint8_t& worm_counter) {
    for (uint8_t i = 0; i < worms_quantity; i++) {
        worms.push_back(std::make_shared<Worm>(battlefield, selected_weapon, selected_gadget_type,
                                               worm_counter++));
    }
}

void Player::destroyAllWormBodies() {
    for (auto& worm: worms) {
        worm->destroyBody();
    }
}

std::unique_ptr<AmmoLeft> Player::getWeaponsAmmo() {
    auto ammo_left = std::make_unique<AmmoLeft>();
    auto it = weapons.cbegin();
    while (it != weapons.cend()) {
        ammo_left->weapon_ammo.insert({it->first, it->second->ammo});
        ++it;
    }
    return ammo_left;
}

void Player::change_weapon(WeaponsAndTools new_weapon) {
    if (weapons.count(new_weapon) != 1) {
        return;
    }
    selected_weapon = &weapons.at(new_weapon);
    selected_gadget_type = new_weapon;
}

Player::Player(Player&& o):
        ready(o.ready),
        is_playing(o.is_playing),
        selected_weapon(o.selected_weapon),
        selected_gadget_type(o.selected_gadget_type),
        worm_turn(o.worm_turn) {
    o.selected_weapon = nullptr;
    o.ready = false;
    o.is_playing = false;
    o.worm_turn = 0;
}
