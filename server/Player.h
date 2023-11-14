#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <map>
#include <list>

#include "../common/const.h"
#include "box2d/box2d.h"
#include "weapon.h"
#include "entity.h"

#define INITIAL_LIFE 100

#define TICK_RATE 30
#define WIDTH 0.9f
#define HEIGHT 1.2f

#define ARM_LENGHT ((WIDTH/2) + 1)

#define POWER_RAISE 1
#define ANGLE_VARIATION (b2_pi/64)

#define INCLINACION_MAX (b2_pi/2)
#define INCLINACION_MIN (-b2_pi/2)

#define CATEGORY_BITS 0x002


class Game;
class Weapon;
class Battlefield;
class Projectile;


class Player : public Entity{
private:


    b2Body* worm;
    float life;
    //std::map<WeaponsAndTools,Weapon >Weapons;
    Weapon* weapon;


    bool facing_right;
    bool is_walking;
    bool ready;
    bool is_jumping;
    bool is_backflipping;

    bool aiming;
    float aim_inclination_degrees; //Radianes
    ADSAngleDir aim_direction;

    bool charging_shoot;
    float weapon_power;

    int facing_factor();

public:
    explicit Player(Battlefield& battlefield);

    void move();
    void stop();
    void jump(const JumpDir& direction);

    void shoot(Game& game, Battlefield& battlefield);

    void change_aim_direction();
    void change_fire_power();

    void set_ready();
    void check_jumping();

    b2Vec2 set_bullet_direction();
    b2Vec2 set_bullet_power();
    float set_bullet_angle();



    void shoot_aim_weapon(std::shared_ptr<Projectile> projectile);
    void use_throwable();
    void use_clickeable_gadget();

    void remove() override;
    bool life_end() override;

    friend class Game;
};

#endif  // PLAYER_H
