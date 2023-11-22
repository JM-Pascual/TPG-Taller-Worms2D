#include "weapon.h"

#include <memory>

#include "battlefield.h"
#include "worm.h"

Weapon::Weapon(uint8_t ammo): ammo(ammo) {}

void Weapon::infiniteAmmo() { ammo = 255; }

//~~~~~~~~~~~~~~~~~~~ Bazooka ~~~~~~~~~~~~~~~~~~~~

Bazooka::Bazooka(): Weapon(BAZOOKA_AMMO) {}


void Bazooka::execute(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();

    std::shared_ptr<Projectile> projectile =
            std::make_shared<BazookaRocket>(battlefield, projectile_position);
    battlefield.add_projectile(projectile);

    worm.shoot_aim_weapon(projectile);

    --ammo;
}


//~~~~~~~~~~~~~~~~~~~ Mortar ~~~~~~~~~~~~~~~~~~~~

// Difiere nada más en la munición, despues el execute es igual al de la bazooka
Mortar::Mortar(): Weapon(MORTAR_AMMO) {}

void Mortar::execute(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();

    std::shared_ptr<Projectile> mortar_rocket =
            std::make_shared<MortarRocket>(battlefield, projectile_position);
    battlefield.add_projectile(mortar_rocket);

    worm.shoot_aim_weapon(mortar_rocket);

    --ammo;
}


//~~~~~~~~~~~~~~~~~~~ Green_grenade ~~~~~~~~~~~~~~~~~~~~

GreenGrenade::GreenGrenade(): Weapon(GREEN_GRENADE_AMMO) {}

void GreenGrenade::execute(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    uint8_t explosion_delay = worm.set_bullet_explosion_delay();

    std::shared_ptr<Projectile> green_grenade =
            std::make_shared<Green>(battlefield, projectile_position, explosion_delay);
    battlefield.add_projectile(green_grenade);

    worm.shoot_aim_weapon(green_grenade);

    --ammo;
}

//~~~~~~~~~~~~~~~~~~~ Green_grenade ~~~~~~~~~~~~~~~~~~~~

RedGrenade::RedGrenade(): Weapon(RED_GRENADE_AMMO) {}

void RedGrenade::execute(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    uint8_t explosion_delay = worm.set_bullet_explosion_delay();

    std::shared_ptr<Projectile> red_grenade =
            std::make_shared<Red>(battlefield, projectile_position, explosion_delay);
    battlefield.add_projectile(red_grenade);

    worm.shoot_aim_weapon(red_grenade);

    --ammo;
}


//~~~~~~~~~~~~~~~~~~~ Banana ~~~~~~~~~~~~~~~~~~~~

BananaGrenade::BananaGrenade(): Weapon(BANANA_AMMO) {}

void BananaGrenade::execute(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    uint8_t explosion_delay = worm.set_bullet_explosion_delay();

    std::shared_ptr<Projectile> banana =
            std::make_shared<Banana>(battlefield, projectile_position, explosion_delay);
    battlefield.add_projectile(banana);

    worm.shoot_aim_weapon(banana);

    --ammo;
}

//~~~~~~~~~~~~~~~~~~~ DynamiteGrenade ~~~~~~~~~~~~~~~~~~~~

DynamiteGrenade::DynamiteGrenade(): Weapon(DYNAMITE_AMMO) {}

void DynamiteGrenade::execute(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    uint8_t explosion_delay = worm.set_bullet_explosion_delay();

    std::shared_ptr<Projectile> dynamite =
            std::make_shared<Dynamite>(battlefield, projectile_position, explosion_delay);
    battlefield.add_projectile(dynamite);

    worm.use_throwable(dynamite);

    --ammo;
}
