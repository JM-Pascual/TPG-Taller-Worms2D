#ifndef WORMS2D_ENTITY_H
#define WORMS2D_ENTITY_H


class Entity {
protected:
    bool collide;
public:
    Entity();
    void start_contact();
    void end_contact();
    ~Entity() = default;
};




#endif //WORMS2D_ENTITY_H
