#include "worm.h"

#include "battlefield.h"
#include "proyectile.h"
#include "weapon.h"

Worm::Worm(Battlefield& battlefield, std::unique_ptr<Weapon>*& selected_weapon,
           WeaponsAndTools& type, const uint8_t& id):
        Entity(battlefield),
        life(INITIAL_LIFE),
        facing_right(true),
        is_walking(false),
        is_jumping(false),
        is_backflipping(false),
        falling(false),
        aiming(false),
        aim_inclination_degrees(0),
        aim_direction(ADSAngleDir::UP),
        charging_shoot(false),
        weapon_power(0),
        selected_weapon(selected_weapon),
        weapon_type(type),
        was_damaged(false),
        id(id) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.position.Set(5.0f, 21.6f);  // Ahora la harcodeo, pero tiene que cambiar
    wormDef.allowSleep = true;
    wormDef.userData.pointer = reinterpret_cast<uintptr_t>(this);  // Todo ver si funciona

    body = battlefield.add_body(wormDef);
    b2PolygonShape wormBox;
    wormBox.SetAsBox(WIDTH / 2, HEIGHT / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wormBox;
    fixtureDef.density = 4.0f;
    fixtureDef.friction = 0.8;

    // fixtureDef.filter.groupIndex = -1; //Todo tengo que ver como seteo cada una de las balas para
    // que pueda colisionar con los gusanos

    body->CreateFixture(&fixtureDef);
}

// Todo puede ser que pueda poner todo en un mismo metodo para ahorrarme un if pero no se si es
// necesario

void Worm::move() {
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = 0.2f * (std::pow(-1, 1 - facing_right) / TICK_RATE) *
            400;                   // todo no se porque si encapsulo no funciona
    body->SetLinearVelocity(vel);  // Esto tengo que ver si esta bien, se ve cuando lo corra
}

void Worm::stop() {
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = 0;
    body->SetLinearVelocity(vel);
}

void Worm::jump(const JumpDir& direction) {
    switch (direction) {
        case (JumpDir::FRONT):
            body->ApplyLinearImpulseToCenter(b2Vec2((facing_factor() * 20), 20), true);
            is_jumping = true;
            break;
        case (JumpDir::BACK):
            body->ApplyLinearImpulseToCenter(b2Vec2(std::pow(-1, facing_right) * 20, 25), true);
            is_backflipping = true;
            break;
    }
}

void Worm::check_jumping() {
    float vel_y = (body->GetLinearVelocity().y);
    if (is_jumping || is_backflipping) {
        if ((vel_y >= 0 && vel_y < 0.002f) || (vel_y <= 0 && vel_y > -0.002f)) {
            is_jumping = false;
            is_backflipping = false;
        }
    }
}

void Worm::check_falling() {
    if (body->GetLinearVelocity() == b2Vec2(0, 0)) {
        falling = false;
    }
}

void Worm::change_aim_direction() {
    if (!aiming) {
        return;
    }

    switch (aim_direction) {

        case ADSAngleDir::UP:

            if (aim_inclination_degrees <= INCLINACION_MAX) {
                aim_inclination_degrees += ANGLE_VARIATION;
            }
            break;
        case ADSAngleDir::DOWN:

            if (aim_inclination_degrees >= INCLINACION_MIN) {
                aim_inclination_degrees -= ANGLE_VARIATION;
            }
            break;
    }
}


void Worm::change_fire_power() {
    if (charging_shoot && weapon_power <= MAX_POWER) {
        weapon_power += POWER_RAISE;
    }
}

void Worm::shoot() { (*selected_weapon)->execute(battlefield, *this); }

b2Vec2 Worm::set_bullet_power() {
    // Fuerza que se le aplica a la bala
    //  f_x = fuerza_total * cos(ang_rad * pi/180)
    //  f_y = fuerza_total * sen(ang_rad * pi/180)
    b2Vec2 bullet_power;
    bullet_power.x = (weapon_power * facing_factor()) * cosf(aim_inclination_degrees);
    bullet_power.y = (weapon_power)*sinf(aim_inclination_degrees);
    return bullet_power;
}

b2Vec2 Worm::set_bullet_direction() {
    // Posición de la bala
    //  x = (body.x + (hip * cos(ang_rad))
    //  y = (body.y + (hip * sen(ang_rad))
    b2Vec2 bullet_position;
    bullet_position.x = (body->GetPosition().x +
                         (facing_factor()) * ARM_LENGHT * cosf(aim_inclination_degrees));
    bullet_position.y = (body->GetPosition().y + (ARM_LENGHT * sinf(aim_inclination_degrees)));
    return bullet_position;
}

float Worm::set_bullet_angle() { return b2Atan2(set_bullet_power().y, set_bullet_power().x); }

uint8_t Worm::set_bullet_explosion_delay() {
    return 3;  // bullet_explosion_delete;
}

void Worm::shoot_aim_weapon(std::shared_ptr<Projectile> projectile) {
    projectile->set_power(set_bullet_power());
}

void Worm::use_throwable(std::shared_ptr<Projectile> throwable) {
    throwable->set_power(b2Vec2(0, 0));
}

int Worm::facing_factor() { return (std::pow(-1, 1 - facing_right)); }

bool Worm::is_dead() {

    if (life <= 0 && not dead) {
        dead = true;
    }
    return dead;
}

void Worm::execute_collision_reaction() {}

void Worm::destroyBody() { battlefield.destroy_body(body); }

Worm::Worm(Worm&& o):
        Entity(o.battlefield),
        life(o.life),
        facing_right(o.facing_right),
        is_walking(o.is_walking),
        is_jumping(o.is_jumping),
        is_backflipping(o.is_backflipping),
        aiming(o.aiming),
        aim_inclination_degrees(o.aim_inclination_degrees),
        aim_direction(o.aim_direction),
        charging_shoot(o.charging_shoot),
        weapon_power(o.weapon_power),
        selected_weapon(o.selected_weapon),
        weapon_type(o.weapon_type),
        id(o.id) {

    o.life = 0;

    o.facing_right = false;
    o.is_walking = false;
    o.is_jumping = false;
    o.is_backflipping = false;

    o.aiming = false;
    o.aim_inclination_degrees = 0.0f;
    o.aim_direction = ADSAngleDir::DOWN;

    o.charging_shoot = false;
    o.weapon_power = 0.0f;
    o.selected_weapon = nullptr;
}

void Worm::stop_all() {
    is_walking = false;
    is_jumping = false;
    is_backflipping = false;
    aiming = false;
    charging_shoot = false;
}
void Worm::start_falling() { falling = true; }

void Worm::recibe_life_modification(float life_variation) {
    if (life_variation < 0) {
        was_damaged = true;
    }

    life += life_variation;
}