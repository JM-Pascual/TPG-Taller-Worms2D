#include "States.h"

WormStateG::WormStateG(const uint8_t& id, const float& x, const float& y,
                       const WeaponsAndTools& equipped_weapon, const bool& is_walking,
                       const bool& is_jumping, const bool& is_backflipping,
                       const bool& facing_right, const bool& was_hit,
                       const float& aim_inclination_degrees, const bool& charging_weapon,
                       const float& life):
        States(StatesTag::WORM_G),
        id(id),
        pos(x, y),
        weapon(equipped_weapon),
        is_walking(is_walking),
        is_jumping(is_jumping),
        is_backflipping(is_backflipping),
        facing_right(facing_right),
        was_hit(was_hit),
        aim_inclination_degrees(aim_inclination_degrees),
        charging_weapon(charging_weapon),
        life(life) {}

ProjectileStateG::ProjectileStateG(const uint8_t& id, const float& x, const float& y,
                                   const WeaponsAndTools& type, const bool& impacted,
                                   const float& angle):
        States(StatesTag::PROJECTILE_G),
        id(id),
        pos(x, y),
        type(type),
        impacted(impacted),
        angle(angle) {}
