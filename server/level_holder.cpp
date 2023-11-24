#include "level_holder.h"

#include "engine.h"

LevelHolder::LevelHolder(Battlefield& battlefield) : battlefield_ref(battlefield) {}

void LevelHolder::add_bar(float x, float y, float angle, bool is_long) {
    bars.emplace_back(battlefield_ref, x, y, angle, is_long);
}

std::shared_ptr<LevelStateG> LevelHolder::get_level_building_state() {
    uint8_t amount_of_bars = bars.size();
    std::vector<BarDto> bars_dto;
    bars_dto.reserve(amount_of_bars);

    for (auto& bar : bars) {
        b2Vec2 bar_pos = bar.get_bar_position();
        bars_dto.emplace_back(
                bar.get_bar_type(),
                bar_pos.x,
                bar_pos.y,
                bar.angle);
    }

    return (std::make_shared<LevelStateG>(amount_of_bars, std::move(bars_dto)));
}
