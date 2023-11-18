#ifndef WORMS2D_LEVEL_HOLDER_H
#define WORMS2D_LEVEL_HOLDER_H

#include <memory>

#include "bar.h"

class Engine;

class Level_holder {
private:
    Bar bar;

public:
    explicit Level_holder(Battlefield& battlefield);
};


#endif  // WORMS2D_LEVEL_HOLDER_H
