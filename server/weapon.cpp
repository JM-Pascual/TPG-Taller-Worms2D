#include "weapon.h"

std::shared_ptr <Projectile>
Weapon::prepare_ammo(Battlefield &battlefield, b2Vec2 projectile_position, float angle, WeaponsAndTools type) {
    std::shared_ptr<Projectile> projectile = std::make_shared<Projectile> (battlefield, projectile_position, angle, type) ;
    battlefield.add_proyectile(projectile);

    return projectile;
}

void Bazooka::execute(Battlefield& battlefield, Player& player) {

    b2Vec2 proyectile_position = player.set_bullet_direction();
    std::shared_ptr<Projectile> projectile  = prepare_ammo(battlefield,proyectile_position,player.set_bullet_angle(),WeaponsAndTools::BAZOOKA);

    player.shoot_aim_weapon(projectile);
}


