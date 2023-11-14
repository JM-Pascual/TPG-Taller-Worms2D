#ifndef WORMS2D_ENTITY_H
#define WORMS2D_ENTITY_H


class Entity {
protected:
    bool collide;
    bool end_life;
public:
    Entity();
    void start_contact();
    void end_contact();
    virtual void remove() = 0;
    virtual bool life_end() = 0; //todo cambiar el nombre
    ~Entity() = default;
};




#endif //WORMS2D_ENTITY_H
