#ifndef WORM_HANDLER_H
#define WORM_HANDLER_H

#include <map>
#include <memory>
#include <mutex>

#include <stdint.h>

#include "../common/const.h"

class Player;
class Worm;

class WormHandler {
private:
    /*
        std::mutex& m; No hace falta este lock, ya que el unico hilo que utiliza estos metodos es el
       gameloop
    */
    std::map<uint8_t, std::unique_ptr<Player>>& players;

    std::shared_ptr<Worm> turn_worm;

    void getTurnWorm(const uint8_t& id, const uint8_t& worm_index);


public:
    explicit WormHandler(std::map<uint8_t, std::unique_ptr<Player>>& players): players(players) {}

    void stop_turn_worm();

    const uint8_t players_alive();

    void clearDamagedState();
    void update_physics();
    void update_weapon();

    // temp protocol
    void player_start_moving(const Direction& direction, const uint8_t& id,
                             const uint8_t& worm_index);
    void player_stop_moving(const uint8_t& id, const uint8_t& worm_index);
    void player_jump(const JumpDir& direction, const uint8_t& id, const uint8_t& worm_index);
    void player_start_aiming(const ADSAngleDir& direction, const uint8_t& id,
                             const uint8_t& worm_index);
    void player_stop_aiming(const uint8_t& id, const uint8_t& worm_index);
    void player_start_charging(const uint8_t& id, const uint8_t& worm_index);
    void player_shoot(const uint8_t& id, const uint8_t& worm_index);

    void player_change_gadget(const WeaponsAndTools& gadget, const uint8_t& id,
                              const uint8_t& worm_index);

    void checkDeadWorms();

    const bool allWormsStayStill();
};


#endif
