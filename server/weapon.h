#ifndef WORMS2D_WEAPON_H
#define WORMS2D_WEAPON_H

#include "../common/const.h"
#include "box2d/b2_math.h"
#include "Player.h"
#include "proyectile.h"


#define BAZOOKA_AMMO uint8_t(10000) //Se supone que tiene que ser infinita
#define GREEN_GRENADE_AMMO uint8_t(10000)
#define BANANA_AMMO uint8_t(5)

class Player;
class Game;
class Battlefield;

class Weapon {
protected:
    uint8_t ammo;
public:

    explicit Weapon(uint8_t ammo);

    virtual void execute(Game& game, Battlefield& battlefield, Player& player_) = 0;

};

//~~~~~~~~~~~~~~~~~~~ Bazooka ~~~~~~~~~~~~~~~~~~~~

class Bazooka : public Weapon{
public:
    Bazooka();
    void execute(Game& game, Battlefield& battlefield, Player& player) override;
    virtual ~Bazooka() = default;
};

//~~~~~~~~~~~~~~~~~~~ Green_grenade ~~~~~~~~~~~~~~~~~~~~

class GreenGrenade : public Weapon{
public:
    GreenGrenade();
    void execute(Game& game, Battlefield& battlefield, Player& player) override;
    virtual ~GreenGrenade() = default;
};

//~~~~~~~~~~~~~~~~~~~ Banana ~~~~~~~~~~~~~~~~~~~~

class BananaGrenade : public Weapon{
    BananaGrenade();
    void execute(Game& game, Battlefield& battlefield, Player& player) override;
    virtual ~BananaGrenade() = default;

};


#endif //WORMS2D_WEAPON_H
