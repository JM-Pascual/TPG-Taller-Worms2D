#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <map>

#include "../common/const.h"
#include "box2d/box2d.h"
#include "battlefield.h"
#include "weapon.h"

#define TICK_RATE 30
#define WIDTH 0.9f
#define HEIGHT 1.2f

#define ARM_LENGHT ((HEIGHT/2) + 1)

#define POWER_RAISE 10
#define ANGLE_VARIATION (b2_pi/32)

#define CATEGORY_BITS 0x002


class Game;
class Weapon;

class Player {
private:
    b2Body* worm;
    //std::map<WeaponsAndTools,Weapon >Weapons;
    Weapon* weapon;
    bool facing_right;
    bool is_moving;
    bool ready;
    bool is_jumping;

    bool aiming;
    float aim_inclination_degrees; //Radianes
    ADSAngleDir aim_direction;

    bool charging_shoot;
    float weapon_power;

public:
    explicit Player(Battlefield& battlefield);

    void move();
    void stop();
    void jump(const JumpDir& direction);
    void shoot(Battlefield& battlefield);

    void change_aim_direction();
    void change_fire_power();

    void set_ready();
    void check_jumping();
    void keep_jumping();

    b2Vec2 set_bullet_direction();
    b2Vec2 set_bullet_power();

    void shoot_aim_weapon(b2Body* bullet);
    void use_throwable();
    void use_clickeable_gadget();

    friend class Game;
};

#endif  // PLAYER_H
