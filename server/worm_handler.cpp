#include "worm_handler.h"

#include <numeric>

#include "Player.h"

void WormHandler::player_start_moving(const Direction& direction, const uint8_t id) {
    players.at(id)->is_walking = true;
    players.at(id)->facing_right = (bool)direction;
    players.at(id)->move();
}

void WormHandler::player_stop_moving(const uint8_t id) {
    players.at(id)->is_walking = false;
    players.at(id)->stop();
}

void WormHandler::player_jump(const JumpDir& direction, const uint8_t id) {
    players.at(id)->jump(direction);
}

void WormHandler::player_start_aiming(const ADSAngleDir& direction, const uint8_t id) {
    players.at(id)->aiming = true;
    players.at(id)->aim_direction = direction;
}

void WormHandler::player_stop_aiming(const uint8_t id) { players.at(id)->aiming = false; }

void WormHandler::player_start_charging(const uint8_t id) { players.at(id)->charging_shoot = true; }

void WormHandler::player_shoot(const uint8_t id) {
    players.at(id)->aiming = false;
    players.at(id)->charging_shoot = false;

    players.at(id)->shoot();

    players.at(id)->weapon_power = 0;
}

void WormHandler::update_weapon() {
    for (auto& [id, player]: players) {
        if (player->aiming) {
            player->change_aim_direction();
        }
        if (player->charging_shoot) {
            player->change_fire_power();
        }
    }
}

void WormHandler::update_physics() {
    for (auto& [id, player]: players) {
        player->check_jumping();
        player->check_falling();
        if (!player->is_walking && !player->is_jumping && !player->is_backflipping &&
            !player->falling) {
            player->stop();
        } else if (player->is_walking) {
            player->move();
        }
    }
}

void WormHandler::stop_all_players() {
    for (auto& player: players) {
        player.second->stop_all();
    }
}

const uint8_t WormHandler::players_alive() {
    uint8_t players_alive = std::accumulate(
            players.begin(), players.end(), 0,
            [](const int& sum, const auto& player) { return sum + player.second->is_playing; });

    return players_alive;
}
