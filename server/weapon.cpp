#include "weapon.h"

#include <memory>

#include "Player.h"
#include "battlefield.h"

Weapon::Weapon(uint8_t ammo): ammo(ammo) {}

//~~~~~~~~~~~~~~~~~~~ Bazooka ~~~~~~~~~~~~~~~~~~~~

Bazooka::Bazooka(): Weapon(BAZOOKA_AMMO) {}


void Bazooka::execute(Battlefield& battlefield, Player& player) {

    b2Vec2 projectile_position = player.set_bullet_direction();

    std::shared_ptr<Projectile> projectile =
            std::make_shared<Rocket>(battlefield, projectile_position);
    battlefield.add_projectile(projectile);

    player.shoot_aim_weapon(projectile);
}


//~~~~~~~~~~~~~~~~~~~ Green_grenade ~~~~~~~~~~~~~~~~~~~~

GreenGrenade::GreenGrenade(): Weapon(GREEN_GRENADE_AMMO) {}

void GreenGrenade::execute(Battlefield& battlefield, Player& player) {
    b2Vec2 projectile_position = player.set_bullet_direction();
    uint8_t explosion_delay = player.set_bullet_explosion_delay();

    std::shared_ptr<Projectile> green_grenade =
            std::make_shared<Green>(battlefield, projectile_position, explosion_delay);
    battlefield.add_projectile(green_grenade);

    player.shoot_aim_weapon(green_grenade);
}

//~~~~~~~~~~~~~~~~~~~ Banana ~~~~~~~~~~~~~~~~~~~~

BananaGrenade::BananaGrenade(): Weapon(BANANA_AMMO) {}

void BananaGrenade::execute(Battlefield& battlefield, Player& player) {

    b2Vec2 projectile_position = player.set_bullet_direction();
    uint8_t explosion_delay = player.set_bullet_explosion_delay();

    std::shared_ptr<Projectile> banana =
            std::make_shared<Banana>(battlefield, projectile_position, explosion_delay);
    battlefield.add_projectile(banana);

    player.shoot_aim_weapon(banana);
}

//~~~~~~~~~~~~~~~~~~~ DynamiteGrenade ~~~~~~~~~~~~~~~~~~~~

DynamiteGrenade::DynamiteGrenade(): Weapon(DYNAMITE_AMMO) {}

void DynamiteGrenade::execute(Battlefield& battlefield, Player& player) {

    b2Vec2 projectile_position = player.set_bullet_direction();
    uint8_t explosion_delay = player.set_bullet_explosion_delay();

    std::shared_ptr<Projectile> dynamite =
            std::make_shared<Dynamite>(battlefield, projectile_position, explosion_delay);
    battlefield.add_projectile(dynamite);

    player.use_throwable(dynamite);
}
