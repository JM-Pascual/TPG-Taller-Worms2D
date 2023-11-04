#include "battlefield.h"

Battlefield::Battlefield(): gravity(X_GRAVITY,Y_GRAVITY), world(std::make_unique<b2World>(gravity)) {
    create_battlefield();
}

void Battlefield::create_battlefield() {

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(100.0f/2, 20.0f/2);
    groundBody->CreateFixture(&groundBox, 0.0f);

    //------------------------------ BAR ----------------------------------------
    //En este caso las dimensiones de las vigas ya estan definidas por enunciado --> 3m/6m x 0.8m

    b2BodyDef barBodyDef;
    barBodyDef.position.Set(38.4f,9.8f);
    bar = world->CreateBody(&barBodyDef);

    b2PolygonShape barBox;
    barBox.SetAsBox(76.8/2, 0.8f/2);
    bar->CreateFixture(&barBox, 0.0f);
}

b2Body* Battlefield::add_body(b2BodyDef bodyDef) {
    return world->CreateBody(&bodyDef);
}

// ToDo Ver si puedo cambiar el nombre, esto queda como un pasamanos pasando este metodo a game para que lo pase a game_loop
void Battlefield::step() {
    world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}
