#include "worm.h"

#include "battlefield.h"
#include "gadget.h"
#include "proyectile.h"

Worm::Worm(Battlefield& battlefield, std::unique_ptr<Gadget>*& selected_weapon,
           WeaponsAndTools& type, const uint8_t& id, const bool& allow_multiple_jump,
           const bool& immortal_worms, b2Vec2 position):
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
        drown(false),
        id(id) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
/*
    auto rng = std::random_device();
    std::mt19937 gen(rng());
    std::uniform_int_distribution<> random(10, 20);

    wormDef.position.Set(random(gen), 21.6f);  // Ahora la harcodeo, pero tiene que cambiar
*/

    wormDef.position = position;
    wormDef.allowSleep = true;
    wormDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    body = battlefield.add_body(wormDef);
    b2CircleShape wormBox;
    wormBox.m_radius = 0.5f;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wormBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 0.0f;
    fixtureDef.filter.groupIndex = -2;

    body->CreateFixture(&fixtureDef);
    body->SetAngularDamping(10.0f);
}

void Worm::reloadAmmo(const uint8_t& ammo) { selected_weapon->get()->addAmmo(ammo); }

void Worm::move() {
    if (not body) {
        return;
    }

    if (body->GetLinearVelocity().LengthSquared() < REFRESH_WALK) {
        this->body->ApplyLinearImpulseToCenter(
                b2Vec2(20 * std::pow(-1, 1 - facing_right) / TICK_RATE, 0), true);
    }

    start_falling();
}

void Worm::stop() {
    if (not body) {
        return;
    }

    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = 0;
    body->SetLinearVelocity(vel);
}

void Worm::jump(const JumpDir& direction) {
    if (not body) {
        return;
    }

    if ((is_jumping || is_backflipping) && (not allow_multiple_jump)) {
        return;
    }

    start_falling();

    switch (direction) {
        case (JumpDir::FRONT):
            body->ApplyLinearImpulseToCenter(b2Vec2((facing_factor() * 5), 5), true);
            is_jumping = true;
            break;
        case (JumpDir::BACK):
            body->ApplyLinearImpulseToCenter(b2Vec2(std::pow(-1, facing_right) * 2, 7), true);
            is_backflipping = true;
            break;
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

void Worm::change_fire_power(TurnHandler& turn_handler) {
    if (charging_shoot) {
        weapon_power += POWER_RAISE;

        if (weapon_power >= MAX_POWER) {
            aiming = false;
            charging_shoot = false;

            shoot(turn_handler);

            weapon_power = 0;
            weapon_delay = DelayAmount::FIVE;
        }
    }
}

void Worm::change_position() {
    body->SetTransform(clicked_position, 0);
    body->SetAwake(true);
}

void Worm::shoot(TurnHandler& turn_handler) {
    if (weapon_power > 0) {
        (*selected_weapon)->shoot(battlefield, *this, turn_handler);
    }
}

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

        reinterpret_cast<Entity*>(body_->GetUserData().pointer)->stop_falling();
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

    o.life = 0.0f;

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

    if (vel.x < MIN_X_VELOCITY) {
        if ((not is_walking || not falling) && not was_damaged && not is_backflipping &&
            not is_jumping) {
            body->SetAwake(false);
        }
    }

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

    if (life < 1) {
        life = 0.0f;
    }
}

void Worm::applyWindResistance(const float& wind_force) {}

float Worm::distance_to_body(b2Body* body_) {
    return (body_->GetWorldCenter() - body->GetWorldCenter()).Length();
}

bool Worm::is_facing_right() { return facing_right; }

void Worm::use_tool() { using_tool = true; }

b2Vec2 Worm::position() { return body->GetWorldCenter(); }
void Worm::open_crate(bool& open) { open = true; }
