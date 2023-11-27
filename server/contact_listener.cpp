#include "contact_listener.h"

#include <iostream>

#include "Player.h"
#include "bar.h"

void Contact_listener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {
    b2ContactListener::PreSolve(contact, oldManifold);

    auto contact2 = contact->GetFixtureB()->GetBody()->GetUserData().pointer;
    auto contact1 = contact->GetFixtureA()->GetBody()->GetUserData().pointer;

    auto* dataB = reinterpret_cast<Entity*>(contact2);
    auto* dataA = reinterpret_cast<Entity*>(contact1);

    if (dataA && dataB) {

        dataA->collision_reaction();
        dataB->collision_reaction();
    }
}
