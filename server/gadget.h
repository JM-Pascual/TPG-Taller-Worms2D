#ifndef WORMS2D_GADGET_H
#define WORMS2D_GADGET_H

#include "../common/const.h"
#include "box2d/b2_math.h"

#include "proyectile.h"


#define BAZOOKA_AMMO uint8_t(255)  // Se supone que tiene que ser infinita
#define GREEN_GRENADE_AMMO uint8_t(255)
#define BANANA_AMMO uint8_t(5)
#define DYNAMITE_AMMO uint8_t(5)
#define MORTAR_AMMO uint8_t(10)
#define RED_GRENADE_AMMO uint8_t(10)
#define TELEPORT_AMMO uint8_t(255)
#define AIRSTRIKE_AMMO uint8_t(2)
#define BASEBALL_BAT_AMMO uint8_t(255)

#define AIRSTRIKE_ROCKETS uint8_t(6)
#define AIRSTRIKE_ROCKET_SEPARATION 0.6f
#define AIRSTRIKE_ROCKET_X_DEVIATION 3.2F
#define AIRSTRIKE_ROCKET_Y_POSITION 22

#define BAT_DAMAGE uint8_t(10)
#define BAT_POWER uint8_t(50)
#define BAT_RANGE uint8_t(4)

class Worm;
class Game;
class Battlefield;

class Gadget{
protected:
    uint8_t ammo;

public:
    explicit Gadget(uint8_t ammo);
    virtual void shoot(Battlefield& battlefield, Worm& worm) = 0;
    ~Gadget() = default;

    friend class Player;
};

//~~~~~~~~~~~~~~~~~~~ GreenGrenade ~~~~~~~~~~~~~~~~~~~~

class GreenGrenade: public Gadget {
public:
    GreenGrenade();
    void shoot(Battlefield& battlefield, Worm& worm) override;
    virtual ~GreenGrenade() = default;
};

//~~~~~~~~~~~~~~~~~~~ RedGrenade ~~~~~~~~~~~~~~~~~~~~

class RedGrenade: public Gadget {
public:
    RedGrenade();
    void shoot(Battlefield& battlefield, Worm& worm) override;
    virtual ~RedGrenade() = default;
};

//~~~~~~~~~~~~~~~~~~~ Banana ~~~~~~~~~~~~~~~~~~~~

class BananaGrenade: public Gadget {
public:
    BananaGrenade();
    void shoot(Battlefield& battlefield, Worm& worm) override;
    virtual ~BananaGrenade() = default;
};

//~~~~~~~~~~~~~~~~~~~ DynamiteGrenade ~~~~~~~~~~~~~~~~~~~~

class DynamiteGrenade: public Gadget {
public:
    DynamiteGrenade();
    void shoot(Battlefield& battlefield, Worm& worm) override;
    virtual ~DynamiteGrenade() = default;
};


//~~~~~~~~~~~~~~~~~~~ Bazooka ~~~~~~~~~~~~~~~~~~~~

class Bazooka: public Gadget {
public:
    Bazooka();
    void shoot(Battlefield& battlefield, Worm& worm) override;
    virtual ~Bazooka() = default;
};

//~~~~~~~~~~~~~~~~~~~ Mortar ~~~~~~~~~~~~~~~~~~~~

class Mortar: public Gadget {
public:
    Mortar();
    void shoot(Battlefield& battlefield, Worm& worm) override;
    virtual ~Mortar() = default;
};

//~~~~~~~~~~~~~~~~~~~ Teleport ~~~~~~~~~~~~~~~~~~~~

class Teleport: public Gadget {
public:
    Teleport();
    void shoot(Battlefield& battlefield, Worm& worm) override;
    virtual ~Teleport() = default;
};

//~~~~~~~~~~~~~~~~~~~ AirStrike ~~~~~~~~~~~~~~~~~~~~

class AirStrike: public Gadget {
public:
    AirStrike();
    void shoot(Battlefield& battlefield, Worm& worm) override;
    virtual ~AirStrike() = default;
};


//~~~~~~~~~~~~~~~~~~~ BaseballBat ~~~~~~~~~~~~~~~~~~~~

class BaseballBat: public Gadget {
private:
    void bat(Battlefield& battlefield, Worm& worm);
    void applyBlastImpulse(b2Body *body_, b2Vec2 blastCenter, b2Vec2 applyPoint, float blastPower, b2Vec2 direction);
public:
    BaseballBat();
    void shoot(Battlefield& battlefield, Worm& worm) override;

    virtual ~BaseballBat() = default;
};

#endif  // WORMS2D_GADGET_H
