#include "info_parser.h"

#include <algorithm>

#include "../common/States.h"

#include "Player.h"
#include "proyectile.h"

void InfoParser::makeLobbyState(std::list<std::shared_ptr<States>>& states) {
    /*
        Sin lock, ya que previamente game coloca el lock
    */
    states.push_back(std::make_shared<PlayerCountL>(players.size()));

    std::transform(players.begin(), players.end(), std::back_inserter(states),
                   [](const auto& player) {
                       return std::make_shared<PlayerStateL>(player.second->ready, player.first);
                   });
}

void InfoParser::makeGameState(std::list<std::shared_ptr<States>>& states) {
    states.push_back(std::make_shared<ProjectileCountG>(projectiles.size()));

    std::transform(projectiles.begin(), projectiles.end(), std::back_inserter(states),
                   [](const auto& projectile) {
                       return projectile.second->get_proyectile_state(projectile.first);
                   });

    std::lock_guard<std::mutex> l(m_game);

    states.push_back(std::make_shared<PlayerCountG>(players.size()));

    std::transform(players.begin(), players.end(), std::back_inserter(states),
                   [](const auto& player) {
                       return std::make_shared<PlayerStateG>(
                               player.first, player.second->body->GetPosition().x,
                               player.second->body->GetPosition().y, player.second->is_walking,
                               player.second->is_jumping, player.second->is_backflipping,
                               player.second->facing_right, player.second->collided,
                               player.second->aim_inclination_degrees,
                               player.second->charging_shoot, player.second->life);
                   });
}
