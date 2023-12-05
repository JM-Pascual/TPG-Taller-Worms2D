#ifndef LEVEL_HOLDER_H
#define LEVEL_HOLDER_H

#include <list>
#include <memory>

#include "../common/States.h"

#include "bar.h"

class Engine;

class LevelHolder {
private:
    Battlefield& battlefield_ref;
    std::list<Bar> bars;

public:
    explicit LevelHolder(Battlefield& battlefield);

    void add_bar(const float& x, const float& y, const float& angle, const bool& is_long);

    std::shared_ptr<LevelStateG> get_level_building_state(const std::string& map_name);
};


#endif  // LEVEL_HOLDER_H
