#include "crate.h"

#include <random>

#include "battlefield.h"

Crate::Crate(Battlefield& battlefield, const uint8_t& id):
        Entity(battlefield),
        type(nullptr),
        _type(_CrateType_::TRAP),
        falling(true),
        was_opened(false),
        crate_id(id) {
    auto rng = std::random_device();
    std::mt19937 gen(rng());
    std::uniform_int_distribution<> random(0, 2);

    _type = (_CrateType_)random(gen);

    switch (_type) {
        case _CrateType_::FIRST_AID:
            type = std::make_unique<FirstAid>();
            break;

        case _CrateType_::AMMO_BOX:
            type = std::make_unique<AmmoBox>();
            break;

        case _CrateType_::TRAP:
            type = std::make_unique<Trap>();
            break;
    }

    b2BodyDef crateDef;
    crateDef.type = b2_dynamicBody;
    crateDef.position.Set(22.0f, 21.6f);  // Ahora la harcodeo, pero tiene que cambiar
    crateDef.allowSleep = true;
    crateDef.userData.pointer = reinterpret_cast<uintptr_t>(this);  // Todo ver si funciona

    body = battlefield.add_body(crateDef);
    b2PolygonShape crateBox;
    crateBox.SetAsBox(CRATE_LENGTH / 2, CRATE_LENGTH / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &crateBox;
    fixtureDef.density = 4.0f;
    fixtureDef.friction = 0.8;

    body->SetGravityScale(0.25);
    body->CreateFixture(&fixtureDef);
}

void Crate::collision_reaction() {
    if (was_opened) {
        return;
    }

    type->collision_reaction(body, battlefield, was_opened);
}

void Crate::stop_falling() { falling = false; }

const bool Crate::wasOpened() { return was_opened; }

Crate::~Crate() { battlefield.destroy_body(this->body); }
