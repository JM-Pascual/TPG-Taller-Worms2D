#include "Player.h"

#include <iostream>


// ToDo Hardocdeado para que los worms aparezcan en la mitad del mapa

Player::Player(Battlefield& battlefield):
        facing_right(true),
        is_walking(false),
        ready(false),
        is_jumping(false),
        is_backflipping(false),
        is_playing(true),
        aiming(false),
        aim_inclination_degrees(0),
        aim_direction(ADSAngleDir::UP),
        charging_shoot(false),
        weapon_power(0),
        entity(GameEntity::WORM) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.position.Set(5.0f, 21.6f);  // Ahora la harcodeo, pero tiene que cambiar
    wormDef.allowSleep = true;
    wormDef.userData.pointer = static_cast<uintptr_t>(entity);

    worm = battlefield.add_body(wormDef);

    b2PolygonShape wormBox;
    wormBox.SetAsBox(WIDTH / 2, HEIGHT / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wormBox;
    fixtureDef.density = 3.0f;
    fixtureDef.restitution = 0;

    // fixtureDef.filter.groupIndex = -1; //Todo tengo que ver como seteo cada una de las balas para
    // que pueda colisionar con los gusanos

    worm->CreateFixture(&fixtureDef);

    weapon = new Bazooka();
}

void Player::set_ready() { ready = !ready; }

// Todo puede ser que pueda poner todo en un mismo metodo para ahorrarme un if pero no se si es
// necesario

void Player::move() {
    b2Vec2 vel = worm->GetLinearVelocity();
    vel.x = 0.2f * (std::pow(-1, 1 - facing_right) / TICK_RATE) * 400;
    worm->SetLinearVelocity(vel);  // Esto tengo que ver si esta bien, se ve cuando lo corra
}

void Player::stop() {
    b2Vec2 vel = worm->GetLinearVelocity();
    vel.x = 0;
    worm->SetLinearVelocity(vel);
}

void Player::jump(const JumpDir& direction) {
    switch (direction) {
        case (JumpDir::FRONT):
            worm->ApplyLinearImpulseToCenter(b2Vec2(std::pow(-1, 1 - facing_right) * 20, 20), true);
            is_jumping = true;
            break;
        case (JumpDir::BACK):
            worm->ApplyLinearImpulseToCenter(b2Vec2(std::pow(-1, facing_right) * 20, 25), true);
            is_backflipping = true;
            break;
    }
}

void Player::check_jumping() {
    float vel_y = (worm->GetLinearVelocity().y);
    if (is_jumping || is_backflipping) {
        if ((vel_y >= 0 && vel_y < 0.002f) || (vel_y <= 0 && vel_y > -0.002f)) {
            is_jumping = false;
            is_backflipping = false;
        }
    }
}

void Player::change_aim_direction() {
    if (!aiming) {
        return;
    }

    switch (aim_direction) {

        case ADSAngleDir::UP:
            aim_inclination_degrees += ANGLE_VARIATION;
            break;
        case ADSAngleDir::DOWN:
            aim_inclination_degrees -= ANGLE_VARIATION;
            break;
    }
}

void Player::change_fire_power() {
    if (charging_shoot) {
        weapon_power += POWER_RAISE;
    }
}

void Player::shoot(Battlefield& battlefield) { weapon->execute(battlefield, *this); }

b2Vec2 Player::set_bullet_power() {
    // Fuerza que se le aplica a la bala
    //  f_x = fuerza_total * cos(ang_rad * pi/180)
    //  f_y = fuerza_total * sen(ang_rad * pi/180)
    b2Vec2 bullet_position;
    bullet_position.x = (weapon_power * cos(aim_inclination_degrees /* * (b2_pi / 180)*/));
    bullet_position.y = (weapon_power * sin(aim_inclination_degrees /* * (b2_pi / 180))*/));
    return bullet_position;
}

b2Vec2 Player::set_bullet_direction() {
    // Posición de la bala
    //  x = (worm.x + hip * cos(ang_rad * pi/18  0)
    //  y = (worm.y + hip * sen(ang_rad * pi/180)
    b2Vec2 bullet_position;
    bullet_position.x = ((worm->GetPosition().x + ARM_LENGHT) * cosf(aim_inclination_degrees));
    bullet_position.y = ((worm->GetPosition().y + ARM_LENGHT) * sinf(aim_inclination_degrees));
    return bullet_position;
}

float Player::set_bullet_angle() { return b2Atan2(set_bullet_power().y, set_bullet_power().x); }

void Player::shoot_aim_weapon(std::shared_ptr<Projectile> projectile) {
    projectile->set_power(set_bullet_power());
}

Player::Player(Player&& o):
        worm(o.worm),
        weapon(o.weapon),
        facing_right(o.facing_right),
        is_walking(o.is_walking),
        ready(o.ready),
        is_jumping(o.is_jumping),
        is_backflipping(o.is_backflipping),
        is_playing(o.is_playing),
        aiming(o.aiming),
        aim_inclination_degrees(o.aim_inclination_degrees),
        aim_direction(o.aim_direction),
        charging_shoot(o.charging_shoot),
        weapon_power(o.weapon_power),
        entity(o.entity) {

    o.worm = nullptr;
    o.weapon = nullptr;

    o.facing_right = false;
    o.is_walking = false;
    o.ready = false;
    o.is_jumping = false;
    o.is_backflipping = false;
    o.is_playing = false;

    o.aiming = false;
    o.aim_inclination_degrees = 0.0f;
    o.aim_direction = ADSAngleDir::DOWN;

    o.charging_shoot = false;
    o.weapon_power = 0.0f;
}

void Player::stop_all() {
    is_walking = false;
    is_jumping = false;
    is_backflipping = false;
    aiming = false;
    charging_shoot = false;
}
