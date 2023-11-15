#include "States.h"

PlayerStateG::PlayerStateG(float x, float y, bool is_walking, bool is_jumping, bool is_backflipping,
                                        bool facing_right, bool was_hit,
                           float aim_inclination_degrees, bool charging_weapon) :
        States(StatesTag::PLAYER_G),
        pos(x, y),
        is_walking(is_walking),
        is_jumping(is_jumping),
        is_backflipping(is_backflipping),
        facing_right(facing_right),
        was_hit(was_hit),
        aim_inclination_degrees(aim_inclination_degrees),
        charging_weapon(charging_weapon){}

ProjectileStateG::ProjectileStateG(const float x, const float y, const WeaponsAndTools type,
                                   const bool impacted, const float angle):
        States(StatesTag::PROJECTILE_G), pos(x, y), type(type), impacted(impacted), angle(angle) {}
