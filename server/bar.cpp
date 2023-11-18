#include "bar.h"

#include "engine.h"

Bar::Bar(Engine& battlefield): Entity(battlefield) {

    b2BodyDef barBodyDef;
    barBodyDef.position.Set(38.4f, 9.2f);

    barBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body = battlefield.add_body(barBodyDef);
    b2PolygonShape barBox;
    barBox.SetAsBox(76.8 / 2, 0.8f / 2);

    body->CreateFixture(&barBox, 0.0f);
}

bool Bar::is_dead() { return dead; }

void Bar::execute_collision_reaction() {}
