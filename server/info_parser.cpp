#include "info_parser.h"

#include <algorithm>
#include <utility>

#include "../common/States.h"

#include "Game.h"
#include "Player.h"
#include "proyectile.h"

void InfoParser::makeLobbyState(std::list<std::shared_ptr<States>>& states) {
    /*
        Sin lock, ya que previamente game coloca el lock
    */
    states.push_back(std::make_shared<PlayerCountL>(game.players.size()));

    std::transform(game.players.begin(), game.players.end(), std::back_inserter(states),
                   [](const auto& player) {
                       return std::make_shared<PlayerStateL>(player.second->ready, player.first);
                   });
}

void InfoParser::makeLevelState(std::list<std::shared_ptr<States>>& states) {
    states.push_back((game.battlefield.level_holder.get_level_building_state()));
}

void InfoParser::makeGameState(std::list<std::shared_ptr<States>>& states,
                               uint8_t id_of_active_player) {

    states.push_back(
            std::make_shared<BattlefieldState>((uint8_t)game.battlefield.engine.wind_force));

    std::transform(game.battlefield.projectiles.begin(), game.battlefield.projectiles.end(),
                   std::back_inserter(states), [](const auto& projectile) {
                       return projectile.second->get_proyectile_state(projectile.first);
                   });

    uint8_t id_of_active_worm = game.players.at(id_of_active_player)
                                        ->worms.at(game.players.at(id_of_active_player)
                                                           ->worm_turn)->id;

    for (const auto& [id, player]: game.players) {
        states.push_back(std::make_shared<PlayerStateG>(
                player->is_playing, id,
                player->calcAvgLife(), player->getWeaponsAmmo()));

        std::transform(player->worms.begin(), player->worms.end(), std::back_inserter(states),
                       [&id_of_active_worm](const auto& worm) {
                           return std::make_shared<WormStateG>(worm->id,
                                   worm->body->GetPosition().x, worm->body->GetPosition().y,
                                   worm->weapon_type,
                                   ((worm->id == id_of_active_worm)),
                                   worm->is_walking, worm->is_jumping, worm->is_backflipping,
                                   worm->facing_right, worm->collided, worm->aim_inclination_degrees,
                                   worm->charging_shoot, worm->life, worm->drown);
                       });
    }
}
