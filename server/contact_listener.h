#ifndef WORMS2D_CONTACT_LISTENER_H
#define WORMS2D_CONTACT_LISTENER_H

#include <box2d/box2d.h>
#include "entity.h"
#include <vector>
#include <memory>



class Contact_listener : public b2ContactListener  {

private:
    std::vector<Entity*> dead_list; //Todo implementar vaciar la lista cuando termina cada turno

public:

    void BeginContact(b2Contact* contact) override;

    void EndContact(b2Contact* contact) override;

    void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

    friend class Battlefield;
};


#endif //WORMS2D_CONTACT_LISTENER_H
