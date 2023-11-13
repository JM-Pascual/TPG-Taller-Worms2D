#ifndef WORMS2D_MY_CONTACT_LISTENER_H
#define WORMS2D_MY_CONTACT_LISTENER_H

#include "box2d/box2d.h"
#include "entity.h"
#include "Player.h"


class My_contact_listener :  public b2ContactListener  {
public:

    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
};


#endif //WORMS2D_MY_CONTACT_LISTENER_H
