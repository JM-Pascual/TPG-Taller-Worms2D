#ifndef WORM_HANDLER_H
#define WORM_HANDLER_H

#include <map>
#include <memory>
#include <mutex>

#include <box2d/b2_math.h>
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


public:
    explicit WormHandler(std::map<uint8_t, std::unique_ptr<Player>>& players);

    void updateTurnWorm(const uint8_t& id, const uint8_t& worm_index);

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
    void player_use_clickable(b2Vec2 position, const uint8_t& id, const uint8_t& worm_index);
    void player_set_delay(DelayAmount delay, const uint8_t& id, const uint8_t& worm_index);

    void player_change_gadget(const WeaponsAndTools& gadget, const uint8_t& id,
                              const uint8_t& worm_index);

    void checkDeadWorms();
    void check_drown_worms();

    void allWorms1HP();

    void playerAllowMultipleJump(const uint8_t& id);

    void makePlayerWormsImmortal(const uint8_t& id);

    void playerInfiniteAmmo(const uint8_t& id);

    void WW3Cheat();

    const bool allWormsStayStill();
};


#endif
