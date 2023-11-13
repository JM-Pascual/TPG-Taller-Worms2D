#include "weapon.h"
#include "battlefield.h"
#include "Game.h"


Weapon::Weapon(uint8_t ammo) : ammo(ammo){}

std::shared_ptr<Projectile>
Weapon::prepare_ammo(Game& game,Battlefield &battlefield, b2Vec2 projectile_position, WeaponsAndTools type, GameEntity entity) {
    std::shared_ptr<Projectile> projectile = std::make_shared<Projectile> (battlefield, projectile_position, type, entity) ;
    game.add_projectile(projectile);

    return projectile;
}


Bazooka::Bazooka() : Weapon(BAZOOKA_AMMO){}

void Bazooka::execute(Game& game, Battlefield& battlefield, Player& player) {

    b2Vec2 proyectile_position = player.set_bullet_direction();
    std::shared_ptr<Projectile> projectile  = prepare_ammo(game, battlefield, proyectile_position, WeaponsAndTools::BAZOOKA,
                                                           GameEntity::BAZOOKA);

    player.shoot_aim_weapon(projectile);
}




