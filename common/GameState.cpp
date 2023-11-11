#include "GameState.h"

PlayerState::PlayerState(const float x, const float y, const bool is_walking, const bool is_jumping,
                         const bool is_backflipping, const bool facing_right,
                         float aim_inclination_degrees) :
        GameState(GameStateTag::PLAYER),
        pos(x, y),
        is_walking(is_walking),
        is_jumping(is_jumping),
        is_backflipping(is_backflipping),
        facing_right(facing_right),
        aim_inclination_degrees(aim_inclination_degrees){}


ProyectileState::ProyectileState(const float x, const float y,
                                 const WeaponsAndTools type,const bool impacted) :
                    GameState(GameStateTag::PROYECTILE),pos(x, y), type(type), impacted(impacted){}

