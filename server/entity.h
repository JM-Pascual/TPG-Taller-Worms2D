#ifndef WORMS2D_ENTITY_H
#define WORMS2D_ENTITY_H

#include <memory>

#include <box2d/box2d.h>

class Battlefield;


class Entity {
protected:
    bool dead;
    b2Body* body;
    Battlefield& battlefield;
    bool collided;

public:
    explicit Entity(Battlefield& battlefield);

    void start_contact();

    void end_contact();

    virtual void applyWindResistence(const float& wind_force) = 0;

    virtual void stop_falling();

    virtual void start_falling();

    virtual void recibe_life_modification(const float& life_variation);

    virtual bool multiple_contact();  // Todo lo vamos a tener que sacar

    virtual bool is_dead();

    virtual void execute_collision_reaction() = 0;

    ~Entity() = default;

    friend class Engine;
};


#endif  // WORMS2D_ENTITY_H
