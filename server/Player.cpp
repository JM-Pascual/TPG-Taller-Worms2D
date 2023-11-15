#include "Player.h"
#include "battlefield.h"


//ToDo Hardocdeado para que los worms aparezcan en la mitad del mapa

Player::Player(Battlefield& battlefield): Entity(battlefield), life(INITIAL_LIFE),facing_right(true), is_walking(false),ready(false),
        is_jumping(false), is_backflipping(false), aiming(false), aim_inclination_degrees(0), aim_direction(ADSAngleDir::UP),
        charging_shoot(false), weapon_power(0) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.position.Set(5.0f, 21.6f); //Ahora la harcodeo, pero tiene que cambiar
    wormDef.userData.pointer = reinterpret_cast<uintptr_t>(this); //Todo ver si funciona
    wormDef.allowSleep = true;

    body = battlefield.add_body(wormDef);
    b2PolygonShape wormBox;
    wormBox.SetAsBox(WIDTH/2 , HEIGHT/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wormBox;
    fixtureDef.density = 3.0f;


    //fixtureDef.filter.groupIndex = -1; //Todo tengo que ver como seteo cada una de las balas para que pueda colisionar con los gusanos

    body->CreateFixture(&fixtureDef);

    weapon = new Bazooka();
}

void Player::set_ready() { ready = !ready; }

//Todo puede ser que pueda poner todo en un mismo metodo para ahorrarme un if pero no se si es necesario

void Player::move() {
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = 0.2f * (std::pow(-1, 1 - facing_right) / TICK_RATE) * 400; //todo no se porque si encapsulo no funciona
    body->SetLinearVelocity(vel);  // Esto tengo que ver si esta bien, se ve cuando lo corra
}

void Player::stop() {
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = 0;
    body->SetLinearVelocity(vel);
}

void Player::jump(const JumpDir& direction) {
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

void Player::check_jumping() {
    float vel_y = (body->GetLinearVelocity().y);
    if (is_jumping || is_backflipping){
        if((vel_y >= 0 && vel_y < 0.002f ) || (vel_y <= 0 && vel_y > -0.002f)){
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



void Player::change_fire_power() {
    if(charging_shoot && weapon_power <= MAX_POWER){
        weapon_power += POWER_RAISE;
    }
}

void Player::shoot(Game &game) {
    weapon->execute(game,battlefield,*this);
}

b2Vec2 Player::set_bullet_power() {
    //Fuerza que se le aplica a la bala
    // f_x = fuerza_total * cos(ang_rad * pi/180)
    // f_y = fuerza_total * sen(ang_rad * pi/180)
    b2Vec2 bullet_power;
    bullet_power.x = (weapon_power * facing_factor()) * cosf(aim_inclination_degrees);
    bullet_power.y = (weapon_power) * sinf(aim_inclination_degrees);
    return bullet_power;
}

b2Vec2 Player::set_bullet_direction(){
    //Posición de la bala
    // x = (body.x + (hip * cos(ang_rad))
    // y = (body.y + (hip * sen(ang_rad))
    b2Vec2 bullet_position;
    bullet_position.x = (body->GetPosition().x + (facing_factor()) * ARM_LENGHT * cosf(aim_inclination_degrees));
    bullet_position.y = (body->GetPosition().y + (ARM_LENGHT * sinf(aim_inclination_degrees)));
    return bullet_position;

}

float Player::set_bullet_angle() {
    return b2Atan2(set_bullet_power().y,set_bullet_power().x);
}

void Player::shoot_aim_weapon(std::shared_ptr<Projectile> projectile) {
    projectile->set_power(set_bullet_power());
}

int Player::facing_factor() {
    return (std::pow(-1, 1 - facing_right));
}

bool Player::still_alive() {
    if(life <= 0 && alive){
        alive = false;
    }else{
        alive = true;
    }
    return alive;
}

void Player::execute_collision_reaction() {

}




