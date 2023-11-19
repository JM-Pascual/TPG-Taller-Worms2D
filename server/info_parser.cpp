#include "info_parser.h"

#include <algorithm>
#include <utility>

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

    states.push_back(std::make_shared<PlayerCountG>(players.size()));

    for (const auto& [id, player]: players) {
        states.push_back(
                std::make_shared<PlayerStateG>(player->is_playing, id, player->getWeaponsAmmo()));
        states.push_back(std::make_shared<WormCountG>(player->worms.size()));

        std::transform(player->worms.begin(), player->worms.end(), std::back_inserter(states),
                       [](const auto& worm) {
                           return std::make_shared<WormStateG>(
                                   worm->id, worm->body->GetPosition().x,
                                   worm->body->GetPosition().y, worm->is_walking, worm->is_jumping,
                                   worm->is_backflipping, worm->facing_right, worm->collided,
                                   worm->aim_inclination_degrees, worm->charging_shoot, worm->life);
                       });
    }
}
