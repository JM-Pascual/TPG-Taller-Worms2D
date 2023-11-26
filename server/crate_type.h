#ifndef CRATE_TYPE_H
#define CRATE_TYPE_H

#include <box2d/box2d.h>

#define MIN_HEALTH_FIRST_AID Config::yamlNode["min_health_first_aid"].as<int>()
#define MAX_HEALTH_FIRST_AID Config::yamlNode["max_health_first_aid"].as<int>()

#define MIN_AMMO_AMMO_BOX Config::yamlNode["min_ammo_ammo_box"].as<int>()
#define MAX_AMMO_AMMO_BOX Config::yamlNode["max_ammo_ammo_box"].as<int>()

#define MIN_DAMAGE_TRAP Config::yamlNode["min_damage_trap"].as<int>()
#define MAX_DAMAGE_TRAP Config::yamlNode["max_damage_trap"].as<int>()

#define CRATE_LENGTH Config::yamlNode["crate_length"].as<float>()

class Battlefield;

class CrateType {
public:
    virtual void collision_reaction(b2Body*& crate_body, Battlefield& battlefield,
                                    bool& was_opened) = 0;
};

class FirstAid: public CrateType {
private:
    uint8_t health_quantity;

public:
    FirstAid();

    void collision_reaction(b2Body*& crate_body, Battlefield& battlefield,
                            bool& was_opened) override;
};

class AmmoBox: public CrateType {
private:
    uint8_t ammo_quantity;

public:
    AmmoBox();

    void collision_reaction(b2Body*& crate_body, Battlefield& battlefield,
                            bool& was_opened) override;
};

class Trap: public CrateType {
private:
    uint8_t epicenter_dmg;

public:
    Trap();

    void collision_reaction(b2Body*& crate_body, Battlefield& battlefield,
                            bool& was_opened) override;
};

#endif
