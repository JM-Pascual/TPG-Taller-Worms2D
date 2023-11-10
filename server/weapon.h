#ifndef WORMS2D_WEAPON_H
#define WORMS2D_WEAPON_H

#include "../common/const.h"
#include "battlefield.h"
#include "box2d/b2_math.h"
#include "player.h"

#define BAZOOKA_AMMO uint8_t(10000) //Se supone que tiene que ser infinita

class Player;

class Weapon {
protected:
    uint8_t ammo;
public:
    explicit Weapon(uint8_t ammo);

    virtual void execute(Battlefield& battlefield, Player& player_) = 0;
    b2Body* prepare_ammo(Battlefield& battlefield, b2Vec2 bullet_position);
};

class Bazooka : public Weapon{

public:
    Bazooka();
    void execute(Battlefield& battlefield, Player& player) override;
};


#endif //WORMS2D_WEAPON_H
