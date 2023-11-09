#include "Player.h"
#include <iostream>
//ToDo Hardocdeado para que los worms aparezcan en la mitad del mapa

Player::Player(Battlefield& battlefield): facing_right(true), is_moving(false),ready(false),is_jumping(false) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.position.Set(0.03f, 21.6f); //Ahora la harcodeo, pero tiene que cambiar
    worm = battlefield.add_body(wormDef);

    b2PolygonShape wormBox;
    wormBox.SetAsBox(WIDTH/2 , HEIGHT/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wormBox;
    fixtureDef.density = 4.0f;

    worm->CreateFixture(&fixtureDef);
    std::cout << worm->GetMass() << std::endl;
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

        case JumpDir::FRONT:
            worm->ApplyLinearImpulseToCenter(b2Vec2(std::pow(-1, 1 - facing_right) * 20,20), true);
            //worm->ApplyForceToCenter(b2Vec2(std::pow(-1, 1 - facing_right) * 20,100),true);
            break;
        case JumpDir::BACK:
            worm->ApplyLinearImpulseToCenter(b2Vec2(std::pow(-1, facing_right) * 5,25), true);
            break;
    }
}

void Player:: check_jumping() {
    float vel_y = (worm->GetLinearVelocity().y);
        if((vel_y >= 0 && vel_y < 0.02f ) || (vel_y <= 0 && vel_y > -0.02f)){
        is_jumping = false;
    }else{
        is_jumping = true;
        is_moving = false;
        std::cout << "x: " <<worm->GetPosition().x << "y: " << worm->GetPosition().y << std::endl;
    }
}

void Player::keep_jumping() {
    float vel_y = worm->GetLinearVelocity().y;
    if (vel_y < -0.2) {
        worm->ApplyForceToCenter(b2Vec2(0, -70), true);
    }
}
