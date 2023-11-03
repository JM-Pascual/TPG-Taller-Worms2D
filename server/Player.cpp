#include "Player.h"

//ToDo Hardocdeado para que los worms aparezcan en la mitad del mapa

Player::Player(std::unique_ptr<b2World>& world): facing_right(true), is_moving(false) {
    b2BodyDef wormDef;
    wormDef.type = b2_dynamicBody;
    wormDef.position.Set(1/PPM, 720/PPM); //Ahora la harcodeo, pero tiene que cambiar
    worm = world->CreateBody(&wormDef);

    b2PolygonShape wormBox;
    wormBox.SetAsBox((PIXEL_WIDTH/PPM)/2 , (PIXEL_HEIGHT/PPM)/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &wormBox;
    fixtureDef.density = 1.0f;

    worm->CreateFixture(&fixtureDef);
}
