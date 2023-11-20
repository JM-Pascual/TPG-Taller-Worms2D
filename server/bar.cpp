#include "bar.h"

#include "battlefield.h"
#include "query_callback.h"

Bar::Bar(Battlefield& battlefield): Entity(battlefield) {
    b2BodyDef barBodyDef;
    barBodyDef.position.Set(38.4f, 9.2f);

    barBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body = battlefield.add_body(barBodyDef);
    b2PolygonShape barBox;
    barBox.SetAsBox(76.8 / 2, 0.8f / 2);

    body->CreateFixture(&barBox, 0.0f);
}

void Bar::execute_collision_reaction() {
    Query_callback queryCallback;
    b2AABB aabb;
    aabb.lowerBound = body->GetPosition();
    aabb.upperBound = body->GetPosition() + b2Vec2(76.8 / 2, 0.8f / 2);
    battlefield.add_query_AABB(&queryCallback, aabb);

    // check which of these bodies have their center of mass within the blast radius
    for (int i = 0; i < queryCallback.found_bodies_size(); i++) {
        b2Body* body_ = queryCallback.found_bodie_at(i);

        reinterpret_cast<Entity*>(body_->GetUserData().pointer)->stop_falling();
    }
}

void Bar::applyWindResistence(const float& wind_force) {}
