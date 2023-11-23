#ifndef WORMS2D_WEAPON_H
#define WORMS2D_WEAPON_H

#include "../common/config.h"
#include "../common/const.h"
#include "box2d/b2_math.h"

#include "proyectile.h"


#define BAZOOKA_AMMO Config::yamlNode["bazooka_ammo"].as<int>()
#define GREEN_GRENADE_AMMO Config::yamlNode["green_grenade_ammo"].as<int>()
#define BANANA_AMMO Config::yamlNode["banana_ammo"].as<int>()
#define DYNAMITE_AMMO Config::yamlNode["dynamite_ammo"].as<int>()
#define MORTAR_AMMO Config::yamlNode["mortar_ammo"].as<int>()
#define RED_GRENADE_AMMO Config::yamlNode["red_grenade_ammo"].as<int>()

class Worm;
class Game;
class Battlefield;

class Weapon {
protected:
    uint8_t ammo;

public:
    explicit Weapon(uint8_t ammo);

    virtual void execute(Battlefield& battlefield, Worm& worm) = 0;

    void infiniteAmmo();

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

//~~~~~~~~~~~~~~~~~~~ Mortar ~~~~~~~~~~~~~~~~~~~~

class Mortar: public Weapon {
public:
    Mortar();
    void execute(Battlefield& battlefield, Worm& worm) override;
    virtual ~Mortar() = default;
};


//~~~~~~~~~~~~~~~~~~~ GreenGrenade ~~~~~~~~~~~~~~~~~~~~

class GreenGrenade: public Weapon {
public:
    GreenGrenade();
    void execute(Battlefield& battlefield, Worm& worm) override;
    virtual ~GreenGrenade() = default;
};

//~~~~~~~~~~~~~~~~~~~ RedGrenade ~~~~~~~~~~~~~~~~~~~~

class RedGrenade: public Weapon {
public:
    RedGrenade();
    void execute(Battlefield& battlefield, Worm& worm) override;
    virtual ~RedGrenade() = default;
};

//~~~~~~~~~~~~~~~~~~~ Banana ~~~~~~~~~~~~~~~~~~~~

class BananaGrenade: public Weapon {
public:
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
