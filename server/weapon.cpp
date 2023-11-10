#include "weapon.h"


Weapon::Weapon(uint8_t ammo): ammo(ammo) {}

b2Body* Weapon::prepare_ammo(Battlefield& battlefield, b2Vec2 bullet_position) {
    b2BodyDef bullet_body;
    bullet_body.type = b2_dynamicBody;
    bullet_body.bullet = true; //Todo ver bien para que sirve
    bullet_body.position = b2Vec2(bullet_position.x ,bullet_position.y);

    b2Body* bullet = battlefield.add_body(bullet_body);


    b2CircleShape shape;
    shape.m_radius = 0.25f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    bullet->CreateFixture(&fixtureDef);

    return bullet;
}


Bazooka::Bazooka() : Weapon(BAZOOKA_AMMO){}


void Bazooka::execute(Battlefield& battlefield, Player& player) {

    b2Vec2 bullet_position = player.set_bullet_direction();
    b2Body* bullet = prepare_ammo(battlefield,bullet_position);

    player.shoot_aim_weapon(bullet);
}


