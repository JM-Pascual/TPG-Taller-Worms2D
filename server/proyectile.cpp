#include "proyectile.h"

Proyectile::Proyectile(b2Body* proyectile, const WeaponsAndTools type): proyectile(proyectile), type(type), impacted(false) {}

std::shared_ptr<ProyectileState> Proyectile::get_proyectile_state() {
    return std::make_shared<ProyectileState>(proyectile->GetPosition().x, proyectile->GetPosition().y, type, impacted);
}
