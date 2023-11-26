#include "States.h"

WormStateG::WormStateG(const uint8_t& id, const float& x, const float& y,
                       const WeaponsAndTools& equipped_weapon, bool on_turn_time,
                       const bool& is_walking, const bool& is_jumping, const bool& is_backflipping,
                       const bool& facing_right, const bool& was_hit,
                       const float& aim_inclination_degrees, const bool& charging_weapon,
                       const float& life, const bool& drown, const bool& using_tool):
        States(StatesTag::WORM_G),
        id(id),
        pos(x, y),
        weapon(equipped_weapon),
        on_turn_time(on_turn_time),
        is_walking(is_walking),
        is_jumping(is_jumping),
        is_backflipping(is_backflipping),
        facing_right(facing_right),
        was_hit(was_hit),
        aim_inclination_degrees(aim_inclination_degrees),
        charging_weapon(charging_weapon),
        life(life),
        drown(drown),
        using_tool(using_tool){}

ProjectileStateG::ProjectileStateG(const uint8_t& id, const float& x, const float& y,
                                   const WeaponsAndTools& type, const bool& impacted,
                                   const float& angle):
        States(StatesTag::PROJECTILE_G),
        id(id),
        pos(x, y),
        type(type),
        impacted(impacted),
        angle(angle) {}

BarDto::BarDto(TerrainActors bar_type, float x, float y, float angle) :
        type(bar_type), x(x), y(y), angle(angle){}
