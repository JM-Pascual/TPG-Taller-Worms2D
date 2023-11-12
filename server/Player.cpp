#include "Player.h"
#include <iostream>

//ToDo Hardocdeado para que los worms aparezcan en la mitad del mapa

Player::Player(Battlefield& battlefield): facing_right(true), is_walking(false),ready(false),
        is_jumping(false), is_backflipping(false), aiming(false), aim_inclination_degrees(0), aim_direction(ADSAngleDir::UP),
        charging_shoot(false), weapon_power(0){
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.position.Set(5.0f, 21.6f); //Ahora la harcodeo, pero tiene que cambiar
    worm = battlefield.add_body(wormDef);

    b2PolygonShape wormBox;
    wormBox.SetAsBox(WIDTH/2 , HEIGHT/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wormBox;
    fixtureDef.density = 3.0f;
    //fixtureDef.filter.groupIndex = -1; //Todo tengo que ver como seteo cada una de las balas para que pueda colisionar con los gusanos

    worm->CreateFixture(&fixtureDef);

    weapon = new Bazooka();
}

void Player::set_ready() { ready = !ready; }

//Todo puede ser que pueda poner todo en un mismo metodo para ahorrarme un if pero no se si es necesario

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
            worm->ApplyLinearImpulseToCenter(b2Vec2(std::pow(-1, 1 - facing_right) * 20,20), true);
            is_jumping = true;
            break;
        case (JumpDir::BACK):
            worm->ApplyLinearImpulseToCenter(b2Vec2(std::pow(-1, facing_right) * 20,25), true);
            is_backflipping = true;
            break;
    }
}

void Player::check_jumping() {
    float vel_y = (worm->GetLinearVelocity().y);
    if (is_jumping || is_backflipping){
        if((vel_y >= 0 && vel_y < 0.002f ) || (vel_y <= 0 && vel_y > -0.002f)){
            is_jumping = false;
            is_backflipping = false;
        }
    }
}

void Player::change_aim_direction() {
    if(!aiming){
        return;
    }

    switch(aim_direction){

        case ADSAngleDir::UP:
            aim_inclination_degrees += ANGLE_VARIATION;
            break;
        case ADSAngleDir::DOWN:
            aim_inclination_degrees -= ANGLE_VARIATION;
            break;
    }
}

void Player::change_fire_power() {
    if(charging_shoot){
        weapon_power += POWER_RAISE;
    }
}

void Player::shoot(Battlefield& battlefield) {
    weapon->execute(battlefield,*this);
}

b2Vec2 Player::set_bullet_power() {
    //Fuerza que se le aplica a la bala
    // f_x = fuerza_total * cos(ang_rad * pi/180)
    // f_y = fuerza_total * sen(ang_rad * pi/180)
    b2Vec2 bullet_position;
    bullet_position.x = (weapon_power * cos(aim_inclination_degrees));;
    bullet_position.y = (weapon_power * sin(aim_inclination_degrees));;
    return bullet_position;
}

b2Vec2 Player::set_bullet_direction(){
    //Posición de la bala
    // x = (worm.x + hip * cos(ang_rad * pi/18  0)
    // y = (worm.y + hip * sen(ang_rad * pi/180)
    b2Vec2 bullet_position;
    bullet_position.x = /*((worm->GetPosition().x + ARM_LENGHT) * cos(aim_inclination_degrees))*/ worm->GetPosition().x + ARM_LENGHT;
    bullet_position.y = /*((worm->GetPosition().y + ARM_LENGHT) * sin(aim_inclination_degrees))*/worm->GetPosition().y;
    return bullet_position;
}

void Player::shoot_aim_weapon(b2Body* bullet) {
    bullet->ApplyLinearImpulseToCenter(set_bullet_power(),true);
}



