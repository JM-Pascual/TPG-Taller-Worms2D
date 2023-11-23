#include "level_holder.h"

#include "engine.h"

Level_holder::Level_holder(Battlefield& battlefield) : battlefield_ref(battlefield) {}

void Level_holder::add_bar(float x, float y, float angle, bool is_long) {
    bars.emplace_back(battlefield_ref, x, y, angle, is_long);
}
