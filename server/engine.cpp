#include "engine.h"

#include <algorithm>

Engine::Engine():
        gravity(X_GRAVITY, Y_GRAVITY), world(std::make_unique<b2World>(gravity)), wind_force(0) {
    listener = new Contact_listener();
    create_battlefield();
    rng = std::mt19937(std::random_device{}());
    random_distribution = std::uniform_real_distribution<float>(MIN_WIND, MAX_WIND);
}

void Engine::create_battlefield() {

    world->SetContactListener(listener);

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -10.0f);

    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(100.0f / 2, 20.0f / 2);
    groundBody->CreateFixture(&groundBox, 0.0f);
}

b2Body* Engine::add_body(b2BodyDef& bodyDef) { return world->CreateBody(&bodyDef); }

// ToDo Ver si puedo cambiar el nombre, esto queda como un pasamanos pasando este metodo a game para
// que lo pase a game_loop
void Engine::step() {
    applyWindForce();
    world->Step(TIME_STEP, VELOCITY_ITERATIONS, POSITION_ITERATIONS);
}

void Engine::destroy_body(b2Body* body) { world->DestroyBody(body); }

void Engine::destroy_dead_entities() {
    // Sin lock ya que el gameloop es el unico hilo que opera con dead_list

    for (auto& entity: listener->dead_list) {
        world->DestroyBody(entity->body);
    }
}

void Engine::clean_dead_entities() { listener->dead_list.clear(); }

void Engine::add_query_AABB(b2QueryCallback* callback, const b2AABB& aabb) {
    world->QueryAABB(callback, aabb);
}

void Engine::newWindForce() { this->wind_force = random_distribution(rng); }

void Engine::applyWindForce() {
    auto body_list = world->GetBodyList();

    for (int32 i = 0; i < world->GetBodyCount(); ++i) {
        auto entity = reinterpret_cast<Entity*>(body_list->GetUserData().pointer);

        if (not entity) {
            continue;
        }

        entity->applyWindResistence(wind_force);

        if (not body_list->GetNext()) {
            break;
        }

        body_list = body_list->GetNext();
    }
}


Engine::~Engine() { delete listener; }
