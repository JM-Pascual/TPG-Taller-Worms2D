#ifndef WORMS2D_ENTITY_H
#define WORMS2D_ENTITY_H

#include <box2d/box2d.h>
class Battlefield;


class Entity {
protected:
    bool collide;
    bool alive;
    b2Body* body;

public:
    Entity();
    void start_contact();
    void end_contact();
    void remove_entity(Battlefield *battlefield); //todo ver si esta bien que sea un puntero
    virtual bool still_alive() = 0; //todo cambiar el nombre
    virtual void execute_collision_reaction(Battlefield& battlefield) = 0;
    ~Entity() = default;
};




#endif //WORMS2D_ENTITY_H
