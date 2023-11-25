#include "gadget.h"

#include <memory>

#include "battlefield.h"
#include "worm.h"

Gadget::Gadget(uint8_t ammo) : ammo(ammo) {}

void Gadget::infiniteAmmo() { ammo = 255; }

//~~~~~~~~~~~~~~~~~~~ Bazooka ~~~~~~~~~~~~~~~~~~~~

Bazooka::Bazooka(): Gadget(BAZOOKA_AMMO) {}


void Bazooka::shoot(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();

    std::shared_ptr<Projectile> projectile =
            std::make_shared<BazookaRocket>(battlefield, projectile_position);
    battlefield.add_projectile(projectile);

    worm.use_chargeable_weapon(projectile);

    --ammo;
}

//~~~~~~~~~~~~~~~~~~~ Mortar ~~~~~~~~~~~~~~~~~~~~

Mortar::Mortar() : Gadget(MORTAR_AMMO){}

void Mortar::shoot(Battlefield &battlefield, Worm &worm) {
    if (ammo == 0) {
        return;
    }
    b2Vec2 projectile_position = worm.set_bullet_direction();

    std::shared_ptr<Projectile> mortar_rocket =
            std::make_shared<MortarRocket>(battlefield, projectile_position);
    battlefield.add_projectile(mortar_rocket);

    worm.use_chargeable_weapon(mortar_rocket);

    --ammo;
}

//~~~~~~~~~~~~~~~~~~~ Green_grenade ~~~~~~~~~~~~~~~~~~~~

GreenGrenade::GreenGrenade(): Gadget(GREEN_GRENADE_AMMO) {}

void GreenGrenade::shoot(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    DelayAmount explosion_delay = worm.grenade_explosion_delay();

    std::shared_ptr<Projectile> green_grenade =
            std::make_shared<Green>(battlefield, projectile_position, float(explosion_delay));
    battlefield.add_projectile(green_grenade);

    worm.use_chargeable_weapon(green_grenade);

    --ammo;
}

//~~~~~~~~~~~~~~~~~~~ Red_grenade ~~~~~~~~~~~~~~~~~~~~

RedGrenade::RedGrenade(): Gadget(RED_GRENADE_AMMO) {}

void RedGrenade::shoot(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    DelayAmount explosion_delay = worm.grenade_explosion_delay();

    std::shared_ptr<Projectile> red_grenade =
            std::make_shared<Red>(battlefield, projectile_position, float(explosion_delay));
    battlefield.add_projectile(red_grenade);

    worm.use_chargeable_weapon(red_grenade);

    --ammo;
}

//~~~~~~~~~~~~~~~~~~~ Banana ~~~~~~~~~~~~~~~~~~~~

BananaGrenade::BananaGrenade(): Gadget(BANANA_AMMO) {}

void BananaGrenade::shoot(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    DelayAmount explosion_delay = worm.grenade_explosion_delay();

    std::shared_ptr<Projectile> banana =
            std::make_shared<Banana>(battlefield, projectile_position, float(explosion_delay));
    battlefield.add_projectile(banana);

    worm.use_chargeable_weapon(banana);

    --ammo;
}


//~~~~~~~~~~~~~~~~~~~ HolyGrenade ~~~~~~~~~~~~~~~~~~~~

HolyGrenade::HolyGrenade() : Gadget(HOLY_GRENADE_AMMO) {}

void HolyGrenade::shoot(Battlefield &battlefield, Worm &worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    DelayAmount explosion_delay = worm.grenade_explosion_delay();

    std::shared_ptr<Projectile> holy_grenade =
            std::make_shared<Holy>(battlefield, projectile_position, float(explosion_delay));
    battlefield.add_projectile(holy_grenade);

    worm.use_positional_weapon(holy_grenade);

    --ammo;
}

//~~~~~~~~~~~~~~~~~~~ DynamiteGrenade ~~~~~~~~~~~~~~~~~~~~

DynamiteGrenade::DynamiteGrenade(): Gadget(DYNAMITE_AMMO) {}

void DynamiteGrenade::shoot(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    DelayAmount explosion_delay = worm.grenade_explosion_delay();

    std::shared_ptr<Projectile> dynamite =
            std::make_shared<Dynamite>(battlefield, projectile_position, float(explosion_delay));
    battlefield.add_projectile(dynamite);

    worm.use_positional_weapon(dynamite);

    --ammo;
}


//~~~~~~~~~~~~~~~~~~~ Teleport ~~~~~~~~~~~~~~~~~~~~

Teleport::Teleport() : Gadget(TELEPORT_AMMO){}

void Teleport::shoot(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }
    worm.change_position();

    --ammo;
}

//~~~~~~~~~~~~~~~~~~~ AirStrike ~~~~~~~~~~~~~~~~~~~~

AirStrike::AirStrike() : Gadget(AIRSTRIKE_AMMO){}

void AirStrike::shoot(Battlefield& battlefield, Worm& worm) {
    if (ammo == 0) {
        return;
    }

    b2Vec2 destination = worm.clicked_position_();
    destination.y =  AIRSTRIKE_ROCKET_Y_POSITION; //Es una altura constante
    destination.x = destination.x - AIRSTRIKE_ROCKET_X_DEVIATION;

    for(int i  = 0; i < AIRSTRIKE_ROCKETS ; i++){

        destination.x += AIRSTRIKE_ROCKET_SEPARATION;

        std::shared_ptr<Projectile> projectile =
                std::make_shared<AirStrikeRocket>(battlefield, destination);
        battlefield.add_projectile(projectile);
    }

    --ammo;
}

//~~~~~~~~~~~~~~~~~~~ BaseballBat ~~~~~~~~~~~~~~~~~~~~

BaseballBat::BaseballBat() : Gadget(BASEBALL_BAT_AMMO) {}

void BaseballBat::shoot(Battlefield &battlefield, Worm &worm) {
    if (ammo == 0) {
        return;
    }
    bat(battlefield,worm);

    --ammo;

}

void BaseballBat::bat(Battlefield& battlefield, Worm& worm) {
    Query_callback queryCallback;
    b2AABB aabb;

    aabb.lowerBound = worm.position() - b2Vec2(BAT_RANGE * (1 - worm.is_facing_right()), BAT_RANGE);
    aabb.upperBound = worm.position() + b2Vec2(BAT_RANGE * (worm.is_facing_right()), BAT_RANGE);

    battlefield.add_query_AABB(&queryCallback, aabb);


    for (int i = 0; i < queryCallback.found_bodies_size(); i++) {
        b2Body* body_ = queryCallback.found_bodie_at(i);

        if (worm.distance_to_body(body_) >= BAT_RANGE)
            continue;

        applyBlastImpulse(body_, worm.position(), body_->GetWorldCenter() , BAT_POWER, worm.set_bullet_angle());
    }
}

void BaseballBat::applyBlastImpulse(b2Body *body_, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower, b2Vec2 direction) {

    b2Vec2 blastDir = applyPoint - blastCenter;
    float distance = blastDir.Normalize();

    if (distance == 0) {
        return;
    }

    Entity* entity = reinterpret_cast<Entity*>(body_->GetUserData().pointer);

    b2Vec2 final_impulse = blastPower * direction;
    entity->apply_explosion(final_impulse);
    entity->recibe_life_modification(-BAT_DAMAGE);
    entity->start_falling();
}


