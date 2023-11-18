#ifndef WORM_HANDLER_H
#define WORM_HANDLER_H

#include <map>
#include <memory>
#include <mutex>

#include <stdint.h>

#include "../common/const.h"

class Player;

class WormHandler {
private:
    /*
        std::mutex& m; No hace falta este lock, ya que el unico hilo que utiliza estos metodos es el
       gameloop
    */
    std::map<uint8_t, std::unique_ptr<Player>>& players;

    // std::unique_ptr<Worm>& getTurnWorm();

public:
    explicit WormHandler(std::map<uint8_t, std::unique_ptr<Player>>& players): players(players) {}

    void stop_all_players();

    const uint8_t players_alive();

    void update_physics();
    void update_weapon();

    // temp protocol
    void player_start_moving(const Direction& direction, uint8_t id);
    void player_stop_moving(uint8_t id);
    void player_jump(const JumpDir& direction, uint8_t id);
    void player_start_aiming(const ADSAngleDir& direction, uint8_t id);
    void player_stop_aiming(const uint8_t id);
    void player_start_charging(const uint8_t id);
    void player_shoot(const uint8_t id);
};


#endif
