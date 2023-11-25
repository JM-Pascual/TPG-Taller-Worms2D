#ifndef CRATE_H
#define CRATE_H

#include <memory>

#include "crate_type.h"
#include "entity.h"

class Battlefield;

class Crate: public Entity {
private:
    std::unique_ptr<CrateType> type;

public:
    const uint8_t crate_id;

    explicit Crate(Battlefield& battlefield, const uint8_t& id);

    void collision_reaction() override;

    void applyWindResistance(const float& wind_force) override {}

    friend class InfoParser;
};

#endif
