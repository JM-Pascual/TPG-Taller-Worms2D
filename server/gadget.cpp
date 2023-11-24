#include "gadget.h"

#include <memory>

#include "battlefield.h"
#include "worm.h"

Gadget::Gadget(uint8_t ammo) : ammo(ammo) {}


//~~~~~~~~~~~~~~~~~~~ Bazooka ~~~~~~~~~~~~~~~~~~~~

Bazooka::Bazooka(): Gadget(BAZOOKA_AMMO) {}


void Bazooka::shoot(Battlefield& battlefield, Worm& worm) {
    if (--ammo <= 0) {
        return;
    }
    /*
    b2Vec2 projectile_position = worm.set_bullet_direction();

    std::shared_ptr<Projectile> projectile =
            std::make_shared<BazookaRocket>(battlefield, projectile_position);
    battlefield.add_projectile(projectile);

    worm.use_chargeable_weapon(projectile);
     */


    b2Vec2 destination = worm.clicked_position_();
    destination.y =  22; //Es una altura constante
    destination.x = destination.x - 3.2f;

    for(int i  = 0; i < AIRSTRIKE_ROCKETS ; i++){
        //tengo que setear una posición difetente para cada caso

        destination.x += 0.6f;

        std::shared_ptr<Projectile> projectile =
                std::make_shared<BazookaRocket>(battlefield, destination);
        battlefield.add_projectile(projectile);

    }
}

//~~~~~~~~~~~~~~~~~~~ Mortar ~~~~~~~~~~~~~~~~~~~~

//Difiere nada más en la munición, despues el shoot es igual al de la bazooka
Mortar::Mortar() : Gadget(MORTAR_AMMO){}

void Mortar::shoot(Battlefield &battlefield, Worm &worm) {
    if (--ammo <= 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();

    std::shared_ptr<Projectile> mortar_rocket =
            std::make_shared<MortarRocket>(battlefield, projectile_position);
    battlefield.add_projectile(mortar_rocket);

    worm.use_chargeable_weapon(mortar_rocket);
}


//~~~~~~~~~~~~~~~~~~~ Green_grenade ~~~~~~~~~~~~~~~~~~~~

GreenGrenade::GreenGrenade(): Gadget(GREEN_GRENADE_AMMO) {}

void GreenGrenade::shoot(Battlefield& battlefield, Worm& worm) {
    if (--ammo <= 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    DelayAmount explosion_delay = worm.grenade_explosion_delay();

    std::shared_ptr<Projectile> green_grenade =
            std::make_shared<Green>(battlefield, projectile_position, float(explosion_delay));
    battlefield.add_projectile(green_grenade);

    worm.use_chargeable_weapon(green_grenade);
}

//~~~~~~~~~~~~~~~~~~~ Green_grenade ~~~~~~~~~~~~~~~~~~~~

RedGrenade::RedGrenade(): Gadget(RED_GRENADE_AMMO) {}

void RedGrenade::shoot(Battlefield& battlefield, Worm& worm) {
    if (--ammo <= 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    DelayAmount explosion_delay = worm.grenade_explosion_delay();

    std::shared_ptr<Projectile> red_grenade =
            std::make_shared<Red>(battlefield, projectile_position, float(explosion_delay));
    battlefield.add_projectile(red_grenade);

    worm.use_chargeable_weapon(red_grenade);
}


//~~~~~~~~~~~~~~~~~~~ Banana ~~~~~~~~~~~~~~~~~~~~

BananaGrenade::BananaGrenade(): Gadget(BANANA_AMMO) {}

void BananaGrenade::shoot(Battlefield& battlefield, Worm& worm) {
    if (--ammo <= 0) {
        return;
    }

    b2Vec2 projectile_position = worm.set_bullet_direction();
    DelayAmount explosion_delay = worm.grenade_explosion_delay();

    std::shared_ptr<Projectile> banana =
            std::make_shared<Banana>(battlefield, projectile_position, float(explosion_delay));
    battlefield.add_projectile(banana);

    worm.use_chargeable_weapon(banana);
}

//~~~~~~~~~~~~~~~~~~~ DynamiteGrenade ~~~~~~~~~~~~~~~~~~~~

DynamiteGrenade::DynamiteGrenade(): Gadget(DYNAMITE_AMMO) {}

void DynamiteGrenade::shoot(Battlefield& battlefield, Worm& worm) {
    if (--ammo <= 0) {
        return;
    }
    /*
    b2Vec2 projectile_position = worm.set_bullet_direction();
    DelayAmount explosion_delay = worm.grenade_explosion_delay();

    std::shared_ptr<Projectile> dynamite =
            std::make_shared<Dynamite>(battlefield, projectile_position, float(explosion_delay));
    battlefield.add_projectile(dynamite);

    worm.use_positional_weapon(dynamite);
     */
    worm.change_position();
}


//~~~~~~~~~~~~~~~~~~~ Teleport ~~~~~~~~~~~~~~~~~~~~

Teleport::Teleport() : Gadget(TELEPORT_AMMO){}

void Teleport::shoot(Battlefield& battlefield, Worm& worm) {
    if (--ammo <= 0) {
        return;
    }
    //Falta hacer el chequeo de la superposición
    worm.change_position();
}

//~~~~~~~~~~~~~~~~~~~ AirStrike ~~~~~~~~~~~~~~~~~~~~

AirStrike::AirStrike() : Gadget(AIRSTRIKE_AMMO){}

void AirStrike::shoot(Battlefield& battlefield, Worm& worm) {
    if (--ammo <= 0) {
        return;
    }

    b2Vec2 destination = worm.clicked_position_();
    destination.y =  AIRSTRIKE_ROCKET_Y_POSITION; //Es una altura constante
    destination.x = destination.x - AIRSTRIKE_ROCKET_X_DEVIATION;

    for(int i  = 0; i < AIRSTRIKE_ROCKETS ; i++){

        destination.x += AIRSTRIKE_ROCKET_SEPARATION;

        std::shared_ptr<Projectile> projectile =
                std::make_shared<BazookaRocket>(battlefield, destination);
        battlefield.add_projectile(projectile);
    }
}
