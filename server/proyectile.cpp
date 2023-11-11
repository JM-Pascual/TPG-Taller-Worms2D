#include "proyectile.h"
#include <iostream>
//Projectile::Projectile(b2Body* projectiles, const WeaponsAndTools type): projectiles(projectiles), type(type), impacted(false) {}


Projectile::Projectile(Battlefield& battlefield, b2Vec2 position, float angle, WeaponsAndTools type) : type(type), impacted(false) {

    b2BodyDef proyectile_body;
    proyectile_body.type = b2_dynamicBody;
    proyectile_body.bullet = true; //Todo ver bien para que sirve
    proyectile_body.position = b2Vec2(position.x , position.y);
    proyectile_body.angle = angle;
    //proyectile_body.angularDamping = 0.01f;

    projectile = battlefield.add_body(proyectile_body);


    b2CircleShape shape;
    shape.m_radius = 0.25f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;

    projectile->CreateFixture(&fixtureDef);
}



std::shared_ptr<ProyectileState> Projectile::upload_state() {
    std::cout << "x: " << projectile->GetPosition().x << " y: " << projectile->GetPosition().y << " " ;
    std::cout << "Angle: "<< projectile->GetAngle()  << "       Angle 2:  "  << (b2Atan2(projectile->GetLinearVelocity().y,projectile->GetLinearVelocity().x)) << " Angular velocity "<< projectile->GetAngularVelocity() << std::endl;

    float vel_angle =  b2Atan2(projectile->GetLinearVelocity().y,projectile->GetLinearVelocity().x);
    return std::make_shared<ProyectileState>(projectile->GetPosition().x, projectile->GetPosition().y, type, impacted,vel_angle);
}

void Projectile::set_power(b2Vec2 power) {
    projectile->ApplyLinearImpulseToCenter(power,true);
}
