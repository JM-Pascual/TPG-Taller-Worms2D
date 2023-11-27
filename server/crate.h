#ifndef CRATE_H
#define CRATE_H

#include <memory>

#include "../common/const.h"

#include "crate_type.h"
#include "entity.h"

class Battlefield;

class Crate: public Entity {
private:
    std::unique_ptr<CrateType> type;
    _CrateType_ _type;
    bool falling;
    bool was_opened;

public:
    const uint8_t crate_id;

    explicit Crate(Battlefield& battlefield, const uint8_t& id);

    void collision_reaction() override;

    void stop_falling() override;

    void applyWindResistance(const float& wind_force) override {}

    const bool wasOpened();

    const bool wasDrown();

    friend class InfoParser;

    ~Crate();
};

#endif
