#include "bar.h"
#include "battlefield.h"

Bar::Bar(Battlefield& battlefield) {

    b2BodyDef barBodyDef;
    barBodyDef.position.Set(38.4f,9.8f);

    barBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    bar = battlefield.add_body(barBodyDef);

    b2PolygonShape barBox;
    barBox.SetAsBox(76.8/2, 0.8f/2);

    bar->CreateFixture(&barBox, 0.0f);
}
