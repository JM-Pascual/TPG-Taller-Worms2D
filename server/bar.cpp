#include "bar.h"

#include "battlefield.h"
#include "query_callback.h"

Bar::Bar(Battlefield& battlefield, float x, float y, float angle, bool is_long): Entity(battlefield) {
    b2BodyDef barBodyDef;
    barBodyDef.position.Set(x, y);
    //angle set in radians

    barBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body = battlefield.add_body(barBodyDef);
    b2PolygonShape barBox;

    if (is_long)
        barBox.SetAsBox(BAR_WIDTH_LONG / 2, BAR_HEIGHT / 2);
    else
        barBox.SetAsBox(BAR_WIDTH_SHORT / 2, BAR_HEIGHT / 2);

    body->CreateFixture(&barBox, 0.0f);
}

void Bar::collision_reaction() {
    Query_callback queryCallback;
    b2AABB aabb;
    aabb.lowerBound = body->GetPosition() - b2Vec2(76.8 / 2, 0.8f / 2);
    aabb.upperBound = body->GetPosition() + b2Vec2(76.8 / 2, 0.8f / 2);
    battlefield.add_query_AABB(&queryCallback, aabb);

    // check which of these bodies have their center of mass within the blast radius
    for (int i = 0; i < queryCallback.found_bodies_size(); i++) {
        b2Body* body_ = queryCallback.found_bodie_at(i);

        reinterpret_cast<Entity*>(body_->GetUserData().pointer)->stop_falling();
    }
}

void Bar::applyWindResistance(const float& wind_force) {}
