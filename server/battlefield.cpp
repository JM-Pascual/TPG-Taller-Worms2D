#include "battlefield.h"

Battlefield::Battlefield(): gravity(X_GRAVITY,Y_GRAVITY), world(std::make_unique<b2World>(gravity)){
    listener = new Contact_listener();
    create_battlefield();
}

void Battlefield::create_battlefield() {

    world->SetContactListener(listener);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(100.0f/2, 20.0f/2);
    groundBody->CreateFixture(&groundBox, 0.0f);
}

b2Body* Battlefield::add_body(b2BodyDef& bodyDef) {
    return world->CreateBody(&bodyDef);
}

// ToDo Ver si puedo cambiar el nombre, esto queda como un pasamanos pasando este metodo a game para que lo pase a game_loop
void Battlefield::step() {
    world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

void Battlefield::destroy_body(b2Body* body) {
    world->DestroyBody(body);
}

void Battlefield::destroy_dead_entities() {
    for(auto entity : listener->dead_list){
        entity->remove_entity(this);
    }
}

void Battlefield::clean_dead_entities() {
    listener->dead_list.clear();
}

void Battlefield::add_query_AABB(b2QueryCallback* callback, const b2AABB& aabb) {
    world->QueryAABB(callback,aabb);
}


