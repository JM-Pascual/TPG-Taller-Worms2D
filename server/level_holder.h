#ifndef LEVEL_HOLDER_H
#define LEVEL_HOLDER_H

#include <memory>
#include <list>

#include "bar.h"

class Engine;

class Level_holder {
private:
    Battlefield& battlefield_ref;
    std::list<Bar> bars;
public:
    explicit Level_holder(Battlefield& battlefield);

    void add_bar(float x, float y, float angle, bool is_long);
};


#endif  // LEVEL_HOLDER_H
