#include "GameState.h"

PlayerState::PlayerState(const float x, const float y, const bool is_walking,
                         const bool facing_right):
        GameState(GameStateTag::PLAYER),
        pos(x, y),
        is_walking(is_walking),
        facing_right(facing_right){}


ProyectileState::ProyectileState(const float x, const float y,const WeaponsAndTools type,const bool impacted) : GameState(GameStateTag::PROYECTILE),pos(x, y)
                                                                                            ,type(type), impacted(impacted){}
