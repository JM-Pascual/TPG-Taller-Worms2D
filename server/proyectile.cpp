#include "proyectile.h"
#include "battlefield.h"

Projectile::Projectile(Battlefield& battlefield, b2Vec2 position, WeaponsAndTools type,
                       const GameEntity entity):
        type(type), entity(entity) {

    b2BodyDef projectile_body;
    projectile_body.type = b2_dynamicBody;
    projectile_body.bullet = true;  // Todo ver bien para que sirve
    projectile_body.position = b2Vec2(position.x, position.y);
    projectile_body.userData.pointer = reinterpret_cast<uintptr_t>(this);
    projectile = battlefield.add_body(projectile_body);


    b2CircleShape shape;
    shape.m_radius = 0.25f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;

    projectile->CreateFixture(&fixtureDef);
}


std::shared_ptr<ProjectileStateG> Projectile::get_proyectile_state() {

    float vel_angle = b2Atan2(projectile->GetLinearVelocity().y, projectile->GetLinearVelocity().x);
    return std::make_shared<ProjectileStateG>(
            projectile->GetPosition().x, projectile->GetPosition().y, type, collide, vel_angle);
}

void Projectile::set_power(b2Vec2 power) { projectile->ApplyLinearImpulseToCenter(power, true); }
