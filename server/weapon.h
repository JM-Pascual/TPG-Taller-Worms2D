#ifndef WORMS2D_WEAPON_H
#define WORMS2D_WEAPON_H

#include "../common/const.h"
#include "box2d/b2_math.h"

#include "proyectile.h"


#define BAZOOKA_AMMO uint8_t(255)  // Se supone que tiene que ser infinita
#define GREEN_GRENADE_AMMO uint8_t(255)
#define BANANA_AMMO uint8_t(5)
#define DYNAMITE_AMMO uint8_t(5)

class Worm;
class Game;
class Battlefield;

class Weapon {
protected:
    uint8_t ammo;

public:
    explicit Weapon(uint8_t ammo);

    virtual void execute(Battlefield& battlefield, Worm& worm) = 0;

    virtual ~Weapon() = default;

    friend class Player;
};

//~~~~~~~~~~~~~~~~~~~ Bazooka ~~~~~~~~~~~~~~~~~~~~

class Bazooka: public Weapon {
public:
    Bazooka();
    void execute(Battlefield& battlefield, Worm& worm) override;
    virtual ~Bazooka() = default;
};

//~~~~~~~~~~~~~~~~~~~ Green_grenade ~~~~~~~~~~~~~~~~~~~~

class GreenGrenade: public Weapon {
public:
    GreenGrenade();
    void execute(Battlefield& battlefield, Worm& worm) override;
    virtual ~GreenGrenade() = default;
};

//~~~~~~~~~~~~~~~~~~~ Banana ~~~~~~~~~~~~~~~~~~~~

class BananaGrenade: public Weapon {
    BananaGrenade();
    void execute(Battlefield& battlefield, Worm& worm) override;
    virtual ~BananaGrenade() = default;
};

//~~~~~~~~~~~~~~~~~~~ DynamiteGrenade ~~~~~~~~~~~~~~~~~~~~

class DynamiteGrenade: public Weapon {
public:
    DynamiteGrenade();
    void execute(Battlefield& battlefield, Worm& worm) override;
    virtual ~DynamiteGrenade() = default;
};


#endif  // WORMS2D_WEAPON_H
