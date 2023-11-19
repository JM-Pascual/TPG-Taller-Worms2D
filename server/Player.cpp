#include "Player.h"

#include <utility>

#include "../common/States.h"

#include "battlefield.h"
#include "engine.h"

// ToDo Hardocdeado para que los worms aparezcan en la mitad del mapa

Player::Player(): ready(false), is_playing(true), weapon(new DynamiteGrenade()), worm_turn(0) {}

void Player::set_ready() { ready = !ready; }

void Player::spawnWorms(Battlefield& battlefield, const uint8_t worms_quantity,
                        uint8_t& worm_counter) {
    for (uint8_t i = 0; i < worms_quantity; i++) {
        worms.push_back(std::make_shared<Worm>(battlefield, weapon, worm_counter++));
    }
}

void Player::destroyAllWormBodies() {
    for (auto& worm: worms) {
        worm->destroyBody();
    }
}

std::unique_ptr<AmmoLeft> Player::getWeaponsAmmo() {
    auto ammo_left = std::make_unique<AmmoLeft>();
    // auto it = weapons.cbegin();
    // while (it != weapons.cend()) {
    //     weapon_ammo.insert({it->first, it->second->ammo});
    //     ++it;
    // }
    ammo_left->weapon_ammo.insert({WeaponsAndTools::DYNAMITE, weapon->ammo});

    return ammo_left;
}

Player::Player(Player&& o):
        ready(o.ready), is_playing(o.is_playing), weapon(o.weapon), worm_turn(o.worm_turn) {
    o.weapon = nullptr;
    o.ready = false;
    o.is_playing = false;
    o.worm_turn = 0;
}

Player::~Player() { delete weapon; }
