#include "proyectile.h"

#include "battlefield.h"

Projectile::Projectile(Battlefield& battlefield, b2Vec2 position, WeaponsAndTools type):
        Entity(battlefield), type(type), blast_radius(2), epicenter_damage(50){  // cambiar

    b2BodyDef projectile_body;
    projectile_body.type = b2_dynamicBody;
    projectile_body.bullet = true;  // Todo ver bien para que sirve
    projectile_body.position = b2Vec2(position.x, position.y);
    projectile_body.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body = battlefield.add_body(projectile_body);

    b2CircleShape shape;
    shape.m_radius = 0.25f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;

    body->CreateFixture(&fixtureDef);
}


std::shared_ptr<ProjectileStateG> Projectile::get_proyectile_state() {

    float vel_angle = b2Atan2(body->GetLinearVelocity().y, body->GetLinearVelocity().x);
    return std::make_shared<ProjectileStateG>(body->GetPosition().x, body->GetPosition().y, type,
                                              dead, vel_angle);
}

void Projectile::set_power(b2Vec2 power) { body->ApplyLinearImpulseToCenter(power, true); }


bool Projectile::is_dead() {
    if (collided && not dead) {
        dead = true;
    }
    return dead;
}

// Este método lo tengo que llamar dentro de contact_listener
void Projectile::execute_collision_reaction() {
    if (type == WeaponsAndTools::BAZOOKA) {
        collide();
    }else if(type == WeaponsAndTools::GREEN_GRENADE){
        collide();
    }
}

void Projectile::collide() {
    Query_callback queryCallback;
    b2AABB aabb;
    aabb.lowerBound = body->GetPosition() - b2Vec2(blast_radius, blast_radius);
    aabb.upperBound = body->GetPosition() + b2Vec2(blast_radius, blast_radius);
    battlefield.add_query_AABB(&queryCallback, aabb);

    // check which of these bodies have their center of mass within the blast radius
    for (int i = 0; i < queryCallback.found_bodies_size(); i++) {
        b2Body* body_ = queryCallback.found_bodie_at(i);
        b2Vec2 bodyCom = body_->GetWorldCenter();

        // ignore bodies outside the blast range
        if ((bodyCom - body->GetWorldCenter()).Length() >= blast_radius)
            continue;

        applyBlastImpulse(body_, body->GetWorldCenter(), bodyCom, epicenter_damage);
        reinterpret_cast<Entity*>(body_->GetUserData().pointer)->start_falling();
    }
}
// Metodo para aplicar impulso a los jugadores colisionados

void Projectile::applyBlastImpulse(b2Body* body_, b2Vec2 blastCenter, b2Vec2 applyPoint,
                                   float blastPower) {

    b2Vec2 blastDir = applyPoint - blastCenter;
    float distance = blastDir.Normalize();
    // ignore bodies exactly at the blast point - blast direction is undefined
    float impulseMag;
    if (distance == 0) {
        return;
    }
    float invDistance = 1 / distance;
    impulseMag = blastPower * invDistance;


    b2Vec2 final_impulse = impulseMag * blastDir;
    body_->ApplyLinearImpulseToCenter(final_impulse, true);

    Entity* entity =  reinterpret_cast<Entity*>(body_->GetUserData().pointer);
    entity->recibe_life_modification(-impulseMag);

}
/*

//~~~~~~~~~~~~~~~~~~~ Rocket ~~~~~~~~~~~~~~~~~~~~


Rocket::Rocket(Battlefield &battlefield, b2Vec2 position):Projectile(battlefield,position, WeaponsAndTools::BAZOOKA){}

void Rocket::execute_collision_reaction() {collide();}

//~~~~~~~~~~~~~~~~~~~ Grenade ~~~~~~~~~~~~~~~~~~~~

Grenade::Grenade(Battlefield &battlefield, b2Vec2 position) :Projectile(battlefield,position, WeaponsAndTools::GREEN_GRENADE),
                                                             explosion_delay(5){}

void Grenade::execute_collision_reaction() {
    if(explosion_delay > 0){
        explosion_delay --;
    }else{
        collide();
    }
}
*/
