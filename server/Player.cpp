#include "Player.h"

//ToDo Hardocdeado para que los worms aparezcan en la mitad del mapa

Player::Player(Battlefield& battlefield): facing_right(true), is_moving(false) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.position.Set(0.03f, 21.6f); //Ahora la harcodeo, pero tiene que cambiar
    //worm = world->CreateBody(&wormDef);
    worm = battlefield.add_body(wormDef);

    b2PolygonShape wormBox;
    wormBox.SetAsBox(WIDTH/2 , HEIGHT/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wormBox;
    fixtureDef.density = 1.0f;

    worm->CreateFixture(&fixtureDef);
}

void Player::set_ready() { ready = !ready; }
