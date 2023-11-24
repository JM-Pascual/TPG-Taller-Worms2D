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
    explicit Crate(Battlefield& battlefield);

    void collision_reaction() override;

    void applyWindResistance(const float& wind_force) override {}
};

#endif
