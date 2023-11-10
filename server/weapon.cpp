#include "weapon.h"


Weapon::Weapon(uint8_t ammo): ammo(ammo) {}

b2Body* Weapon::prepare_ammo(Battlefield& battlefield, b2Vec2 proyectile_position, WeaponsAndTools type) {
    b2BodyDef proyectile_body;
    proyectile_body.type = b2_dynamicBody;
    proyectile_body.bullet = true; //Todo ver bien para que sirve
    proyectile_body.position = b2Vec2(proyectile_position.x , proyectile_position.y);

    b2Body* world_proyectile = battlefield.add_body(proyectile_body);


    b2CircleShape shape;
    shape.m_radius = 0.25f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    world_proyectile->CreateFixture(&fixtureDef);

    std::shared_ptr<Proyectile> proyectile = std::make_shared<Proyectile> (world_proyectile,type) ;
    battlefield.add_proyectile(proyectile);

    return world_proyectile;
}


Bazooka::Bazooka() : Weapon(BAZOOKA_AMMO){}

void Bazooka::execute(Battlefield& battlefield, Player& player) {

    b2Vec2 proyectile_position = player.set_bullet_direction();
    b2Body* proyectile = prepare_ammo(battlefield,proyectile_position,WeaponsAndTools::BAZOOKA);

    player.shoot_aim_weapon(proyectile);
}


