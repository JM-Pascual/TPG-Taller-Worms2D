#include "proyectile.h"
#include <iostream>

Projectile::Projectile(Battlefield &battlefield, b2Vec2 position, WeaponsAndTools type, const GameEntity entity)
        : type(type), impacted(false), entity(entity) {

    b2BodyDef projectile_body;
    projectile_body.type = b2_dynamicBody;
    projectile_body.bullet = true; //Todo ver bien para que sirve
    projectile_body.position = b2Vec2(position.x , position.y);
    //projectile_body.userData.pointer = static_cast<uintptr_t>(entity); //Es necesario si o si por la biblioteca que pase un puntero
    projectile_body.userData.pointer = reinterpret_cast<uintptr_t>((&entity));
    projectile = battlefield.add_body(projectile_body);



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
