#ifndef LEVEL_HOLDER_H
#define LEVEL_HOLDER_H

#include <memory>
#include <list>

#include "bar.h"

#include "../common/States.h"

class Engine;

class LevelHolder {
private:
    Battlefield& battlefield_ref;
    std::list<Bar> bars;
public:
    explicit LevelHolder(Battlefield& battlefield);

    void add_bar(float x, float y, float angle, bool is_long);

    std::shared_ptr<LevelStateG> get_level_building_state();
};


#endif  // LEVEL_HOLDER_H
