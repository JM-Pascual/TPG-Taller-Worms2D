#include "bar.h"

#include "battlefield.h"
#include "query_callback.h"

Bar::Bar(Battlefield& battlefield, float x, float y, float inclination_angle, bool is_long):
        Entity(battlefield) {
    b2BodyDef barBodyDef;
    barBodyDef.position.Set(x, y);

    barBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);

    angle = inclination_angle;
    barBodyDef.angle = inclination_angle;

    body = battlefield.add_body(barBodyDef);
    b2PolygonShape barBox;
    b2FixtureDef fixture;

    if (is_long) {
        width = BAR_WIDTH_LONG;
        barBox.SetAsBox(width / 2, BAR_HEIGHT / 2);
    } else {
        width = BAR_WIDTH_SHORT;
        barBox.SetAsBox(width / 2, BAR_HEIGHT / 2);
    }

    fixture.shape = &barBox;
    fixture.density = 0.0f;
    fixture.friction = 1.0f;

    body->CreateFixture(&fixture);
}

b2Vec2 Bar::get_bar_position() { return (body->GetPosition()); }

TerrainActors Bar::get_bar_type() const {
    if (width == BAR_WIDTH_LONG)
        return TerrainActors::LONG_BAR;
    else
        return TerrainActors::BAR;
}

float Bar::get_bar_width() const { return (width); }

float Bar::get_bar_height() const { return (BAR_HEIGHT); }

#include <iostream>
void Bar::collision_reaction(b2Vec2 normal) {
    Query_callback queryCallback;
    b2AABB aabb{};
    aabb.lowerBound = get_bar_position() - b2Vec2(width , BAR_HEIGHT * 2);
    aabb.upperBound = get_bar_position() + b2Vec2(width , BAR_HEIGHT * 2);
    battlefield.add_query_AABB(&queryCallback, aabb);

    // check which of these bodies have their center of mass within the blast radius
    for (int i = 0; i < queryCallback.found_bodies_size(); i++) {
        b2Body *body_ = queryCallback.found_bodie_at(i);

        // 0 < Angulo < 45 || 135 < Angulo < 180
        //std::cout << "x: " << normal.x << "  y: "<<normal.y << std::endl;

        if (std::abs(sinf(angle)) > (std::sqrt(2) / 2) ) //|| normal.y <= 0.005f)
            continue;
        /*
        if((std::abs(sinf(angle)) == 0 && normal.y < 1.0f))
            continue;
        */
        std::cout << std::abs(std::atan2(normal.y, normal.x )) + std::abs(angle) << " angle: "<< angle << "normal angle "<< std::atan2(normal.y, normal.x ) <<  std::endl;
        float normal_angle;
        normal_angle = std::atan2(normal.y, normal.x );

        if((std::atan2(normal.y, normal.x ) > b2_pi/2)){
            normal_angle = std::atan2(normal.y, normal.x ) - b2_pi/2;
        }

        if((normal_angle + std::abs(angle) > 1.56f && normal_angle +  std::abs(angle) < 1.58f)){
           if(normal.y >= 0)
            reinterpret_cast<Entity *>(body_->GetUserData().pointer)->stop_falling();
        }

    }
}
void Bar::applyWindResistance(const float& wind_force) {}
