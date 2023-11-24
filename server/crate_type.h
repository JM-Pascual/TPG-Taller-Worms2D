#ifndef CRATE_TYPE_H
#define CRATE_TYPE_H

#include <box2d/box2d.h>

#define MIN_HEALTH_FIRST_AID 10
#define MAX_HEALTH_FIRST_AID 50

#define MIN_AMMO_AMMO_BOX 3
#define MAX_AMMO_AMMO_BOX 10

#define MIN_DAMAGE_TRAP 10
#define MAX_DAMAGE_TRAP 100

#define CRATE_LENGTH 0.8

class Battlefield;

enum class _CrateType_ { FIRST_AID, AMMO_BOX, TRAP };

class CrateType {
public:
    virtual void collision_reaction(b2Body*& crate_body, Battlefield& battlefield) = 0;
};

class FirstAid: public CrateType {
private:
    uint8_t health_quantity;

public:
    FirstAid();

    void collision_reaction(b2Body*& crate_body, Battlefield& battlefield) override;
};

class AmmoBox: public CrateType {
private:
    uint8_t ammo_quantity;

public:
    AmmoBox();

    void collision_reaction(b2Body*& crate_body, Battlefield& battlefield) override;
};

class Trap: public CrateType {
private:
    uint8_t epicenter_dmg;

public:
    Trap();

    void collision_reaction(b2Body*& crate_body, Battlefield& battlefield) override;
};

#endif
