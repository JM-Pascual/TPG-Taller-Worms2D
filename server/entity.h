#ifndef WORMS2D_ENTITY_H
#define WORMS2D_ENTITY_H

#include <box2d/box2d.h>
class Battlefield;


class Entity {
protected:
    bool dead;
    b2Body* body;
    Battlefield& battlefield;
    bool collided;

public:
    Entity(Battlefield& battlefield);
    void start_contact();
    void end_contact();
    virtual void start_falling();
    virtual void recibe_life_modification(float life_variation);
    virtual bool multiple_contact(); //Todo lo vamos a tener que sacar
    void remove_entity();
    virtual bool is_dead() = 0;
    virtual void execute_collision_reaction() = 0;
    ~Entity() = default;
};


#endif  // WORMS2D_ENTITY_H
