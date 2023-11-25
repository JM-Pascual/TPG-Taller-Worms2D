#include "worm_handler.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <numeric>

#include "Player.h"
#include "worm.h"

WormHandler::WormHandler(std::map<uint8_t, std::unique_ptr<Player>>& players): players(players) {
    srand(time(NULL));
}

void WormHandler::getTurnWorm(const uint8_t& id, const uint8_t& worm_index) {
    turn_worm = players.at(id)->worms.at(worm_index);
}

void WormHandler::player_start_moving(const Direction& direction, const uint8_t& id,
                                      const uint8_t& worm_index) {
    getTurnWorm(id, worm_index);

    turn_worm->is_walking = true;
    turn_worm->facing_right = (bool)direction;
    turn_worm->move();
}

void WormHandler::player_stop_moving(const uint8_t& id, const uint8_t& worm_index) {
    getTurnWorm(id, worm_index);

    turn_worm->is_walking = false;
    turn_worm->stop();
}

void WormHandler::player_jump(const JumpDir& direction, const uint8_t& id,
                              const uint8_t& worm_index) {
    getTurnWorm(id, worm_index);

    turn_worm->jump(direction);
}

void WormHandler::player_start_aiming(const ADSAngleDir& direction, const uint8_t& id,
                                      const uint8_t& worm_index) {
    getTurnWorm(id, worm_index);

    turn_worm->aiming = true;
    turn_worm->aim_direction = direction;
}

void WormHandler::player_stop_aiming(const uint8_t& id, const uint8_t& worm_index) {
    getTurnWorm(id, worm_index);
    turn_worm->aiming = false;
}

void WormHandler::player_start_charging(const uint8_t& id, const uint8_t& worm_index) {
    getTurnWorm(id, worm_index);
    turn_worm->charging_shoot = true;
}

void WormHandler::player_shoot(const uint8_t& id, const uint8_t& worm_index) {
    getTurnWorm(id, worm_index);

    turn_worm->aiming = false;
    turn_worm->charging_shoot = false;

    turn_worm->shoot();

    turn_worm->weapon_power = 0;
    turn_worm->weapon_delay = DelayAmount::FIVE;
}

void WormHandler::player_use_clickable(b2Vec2 position, const uint8_t& id, const uint8_t& worm_index) {
    getTurnWorm(id, worm_index);
    turn_worm->change_clicked_position(position);
}

void WormHandler::player_set_delay(DelayAmount delay, const uint8_t &id, const uint8_t &worm_index) {
    getTurnWorm(id, worm_index);
    turn_worm->change_bullet_explosion_delay(delay);
}


void WormHandler::player_change_gadget(const WeaponsAndTools& gadget, const uint8_t& id,
                                       const uint8_t& worm_index) {
    getTurnWorm(id, worm_index);
    players.at(id)->change_weapon(gadget);
}

void WormHandler::clearDamagedState() {
    for (const auto& [id, player]: players) {
        for (const auto& worm: player->worms) {
            worm->was_damaged = false;
        }
    }
}

void WormHandler::update_weapon() {
    if (not turn_worm) {
        return;
    }

    if (turn_worm->aiming) {
        turn_worm->change_aim_direction();
    }
    if (turn_worm->charging_shoot) {
        turn_worm->change_fire_power();
    }
}


void WormHandler::update_physics() {
    if (not turn_worm) {
        return;
    }

    if (!turn_worm->is_walking && !turn_worm->is_jumping && !turn_worm->is_backflipping &&
        !turn_worm->falling) {
        turn_worm->stop();
    } else if (turn_worm->is_walking) {
        turn_worm->move();
    }
}

void WormHandler::stop_turn_worm() {
    if (not turn_worm) {
        return;
    }

    turn_worm->stop_all();
}

const uint8_t WormHandler::players_alive() {
    uint8_t players_alive = std::accumulate(
            players.begin(), players.end(), 0,
            [](const int& sum, const auto& player) { return sum + player.second->is_playing; });

    return players_alive;
}

void WormHandler::checkDeadWorms() {
    for (const auto& [id, player]: players) {

        auto it = player->worms.cbegin();
        while (it != player->worms.cend()) {
            if ((*it)->life == 0) {
                (*it)->destroyBody();
                it = player->worms.erase(it);

                continue;
            }

            ++it;
        }

        if (player->worms.empty()) {
            player->is_playing = false;
        }
    }
}

const bool WormHandler::allWormsStayStill() {
    for (const auto& [id, player]: players) {
        for (const auto& worm: player->worms) {
            // cppcheck-suppress useStlAlgorithm
            if (worm->falling) {
                return false;
            }
        }
    }

    return true;
}




void WormHandler::allWorms1HP() {
    for (const auto& [id, player]: players) {
        for (const auto& worm: player->worms) {
            worm->life = 1;
        }
    }
}

void WormHandler::playerAllowMultipleJump(const uint8_t& id) {
    players.at(id)->allow_multiple_jump = !players.at(id)->allow_multiple_jump;
}

void WormHandler::makePlayerWormsImmortal(const uint8_t& id) {
    players.at(id)->immortal_worms = !players.at(id)->immortal_worms;
}

void WormHandler::killRandomWorm() {
    auto& player = players.at(rand() % players.size());
    size_t worm_idx = rand() % player->worms.size();
    player->worms.at(worm_idx)->destroyBody();
    player->worms.erase(player->worms.begin() + worm_idx);
}

void WormHandler::playerInfiniteAmmo(const uint8_t& id) { players.at(id)->infiniteAmmo(); }
