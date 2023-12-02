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

public:
    explicit Entity(Battlefield& battlefield);

    virtual void applyWindResistance(const float& wind_force) = 0;

    virtual void apply_explosion(const b2Vec2& final_impulse);

    virtual void stop_falling();

    virtual void start_falling();

    virtual void recibe_life_modification(const float& life_variation);

    virtual inline void reloadAmmo(const uint8_t& ammo) {}

    virtual bool is_dead();

    virtual inline void open_crate(bool& open) {}

    virtual void collision_reaction(const b2Vec2& normal) = 0;

    virtual ~Entity();

    friend class Engine;
};


#endif  // WORMS2D_ENTITY_H
