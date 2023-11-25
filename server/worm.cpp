#include "worm.h"

#include "battlefield.h"
#include "gadget.h"
#include "proyectile.h"

Worm::Worm(Battlefield& battlefield, std::unique_ptr<Gadget>*& selected_weapon,
           WeaponsAndTools& type, const uint8_t& id, const bool& allow_multiple_jump,
           const bool& immortal_worms):
        Entity(battlefield),
        life(INITIAL_LIFE),
        facing_right(true),
        is_walking(false),
        is_jumping(false),
        is_backflipping(false),
        falling(false),
        using_tool(false),
        aiming(false),
        aim_inclination_degrees(0),
        aim_direction(ADSAngleDir::UP),
        charging_shoot(false),
        weapon_power(0),
        weapon_delay(DelayAmount::FIVE),
        clicked_position(0, 0),
        selected_weapon(selected_weapon),
        weapon_type(type),
        was_damaged(false),
        pos_y_before_falling(0.0f),
        allow_multiple_jump(allow_multiple_jump),
        immortal_worms(immortal_worms),
        id(id) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.position.Set(22.0f, 21.6f);  // Ahora la harcodeo, pero tiene que cambiar
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
    if (not body) {
        return;
    }

    if (body->GetLinearVelocity().LengthSquared() < 10) {
        this->body->ApplyLinearImpulseToCenter(
                b2Vec2(80 * std::pow(-1, 1 - facing_right) / TICK_RATE, 0), true);
    }
}

void Worm::stop() {
    if (not body) {
        return;
    }

    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = 0;
    body->SetLinearVelocity(vel);
    body->SetAwake(false);
}

void Worm::jump(const JumpDir& direction) {
    if (not body) {
        return;
    }

    if ((is_jumping || is_backflipping) && (not allow_multiple_jump)) {
        return;
    }

    switch (direction) {
        case (JumpDir::FRONT):
            body->ApplyLinearImpulseToCenter(b2Vec2((facing_factor() * 20), 20), true);
            is_jumping = true;
            break;
        case (JumpDir::BACK):
            body->ApplyLinearImpulseToCenter(b2Vec2(std::pow(-1, facing_right) * 10, 35), true);
            is_backflipping = true;
            break;
    }

    start_falling();
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

void Worm::change_position() {
    body->SetTransform(clicked_position, 0);
    body->SetAwake(true);
}

void Worm::shoot() { (*selected_weapon)->shoot(battlefield, *this); }

void Worm::use_chargeable_weapon(const std::shared_ptr<Projectile>& projectile) {
    projectile->set_power(set_bullet_power());
}

void Worm::use_positional_weapon(const std::shared_ptr<Projectile>& throwable) {
    throwable->set_power(b2Vec2(0, 0));
}


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
    b2Vec2 bullet_position;
    bullet_position.x = (body->GetPosition().x +
                         (facing_factor()) * ARM_LENGHT * cosf(aim_inclination_degrees));
    bullet_position.y = (body->GetPosition().y + (ARM_LENGHT * sinf(aim_inclination_degrees)));
    return bullet_position;
}
// todo cambiar nombre
b2Vec2 Worm::set_bullet_angle() {
    return b2Vec2(facing_factor() * cosf(aim_inclination_degrees), sinf(aim_inclination_degrees));
}

void Worm::change_bullet_explosion_delay(DelayAmount delay) { weapon_delay = delay; }

void Worm::change_clicked_position(b2Vec2 new_position) {
    using_tool = true;
    clicked_position = new_position;
}

b2Vec2 Worm::clicked_position_() { return clicked_position; }

DelayAmount Worm::grenade_explosion_delay() { return weapon_delay; }


int Worm::facing_factor() { return (std::pow(-1, 1 - facing_right)); }

bool Worm::is_dead() {

    if (life <= 0 && not dead) {
        dead = true;
    }
    return dead;
}

void Worm::collision_reaction() {
    Query_callback queryCallback;
    b2AABB aabb{};
    aabb.lowerBound = body->GetWorldCenter() - b2Vec2(WIDTH / 2, HEIGHT / 2);
    aabb.upperBound = body->GetWorldCenter() + b2Vec2(WIDTH / 2, HEIGHT / 2);
    battlefield.add_query_AABB(&queryCallback, aabb);

    // check which of these bodies have their center of mass within the blast radius
    for (int i = 0; i < queryCallback.found_bodies_size(); i++) {
        b2Body* body_ = queryCallback.found_bodie_at(i);

        reinterpret_cast<Entity*>(body_->GetUserData().pointer)->stop_falling(0);
    }
}

void Worm::destroyBody() {
    battlefield.destroy_body(body);
    body = nullptr;
}

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
        weapon_delay(o.weapon_delay),
        selected_weapon(o.selected_weapon),
        weapon_type(o.weapon_type),
        pos_y_before_falling(o.pos_y_before_falling),
        allow_multiple_jump(o.allow_multiple_jump),
        immortal_worms(o.immortal_worms),
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
    o.weapon_delay = DelayAmount::FIVE;
    o.selected_weapon = nullptr;

    o.pos_y_before_falling = 0.0f;
}

void Worm::stop_all() {
    is_walking = false;
    aiming = false;
    charging_shoot = false;
}

void Worm::start_falling() {
    pos_y_before_falling = body->GetPosition().y;
    falling = true;
}

void Worm::stop_falling() {
    if (not body) {
        return;
    }

    auto vel = body->GetLinearVelocity();

    if (vel.y < MIN_Y_VELOCITY) {
        is_jumping = false;
        is_backflipping = false;
    }

    if (body->GetLinearVelocity().LengthSquared() < MIN_SQUARED_VELOCITY) {
        falling = false;

        float fall_dmg = (pos_y_before_falling - body->GetPosition().y) * FALL_DMG_AMP;

        if (fall_dmg > MIN_FALLING_DAMAGE_HEIGHT) {
            recibe_life_modification(fall_dmg > MAX_FALLING_DAMAGE ? -MAX_FALLING_DAMAGE :
                                                                     -fall_dmg);
        }

        pos_y_before_falling = 0.0f;
    }
}

void Worm::recibe_life_modification(const float& life_variation) {
    if (immortal_worms) {
        return;
    }

    if (life_variation < 0) {
        was_damaged = true;
    }

    life += life_variation;

    if (life < 0) {
        life = 0;
    }
}

void Worm::applyWindResistance(const float& wind_force) {}

float Worm::distance_to_body(b2Body* body_) {
    return (body_->GetWorldCenter() - body->GetWorldCenter()).Length();
}

b2Vec2 Worm::position() { return body->GetWorldCenter(); }

bool Worm::is_facing_right() { return facing_right; }
