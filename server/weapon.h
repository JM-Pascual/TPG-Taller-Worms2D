#ifndef WORMS2D_WEAPON_H
#define WORMS2D_WEAPON_H

#include "../common/const.h"
#include "battlefield.h"
#include "box2d/b2_math.h"
#include "Player.h"
#include "proyectile.h"

#define BAZOOKA_AMMO uint8_t(10000) //Se supone que tiene que ser infinita

class Player;

class Weapon {
protected:
    uint8_t ammo;
public:
    explicit Weapon() = default;

    virtual void execute(Battlefield& battlefield, Player& player_) = 0;
    virtual std::shared_ptr<Projectile> prepare_ammo(Battlefield& battlefield, b2Vec2 projectile_position, float angle, WeaponsAndTools type);

};

class Bazooka : public Weapon{
    uint8_t ammo = BAZOOKA_AMMO;
public:
    Bazooka() = default;
    void execute(Battlefield& battlefield, Player& player) override;
};


#endif //WORMS2D_WEAPON_H
