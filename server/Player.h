#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <map>
#include <memory>

#include <box2d/box2d.h>

#include "../common/const.h"

#include "entity.h"
#include "weapon.h"

#define INITIAL_LIFE 100

#define TICK_RATE 30
#define WIDTH 0.9f
#define HEIGHT 1.2f

#define ARM_LENGHT ((WIDTH / 2) + 2)

#define POWER_RAISE 1
#define MAX_POWER 10
#define ANGLE_VARIATION (b2_pi / 64)

#define INCLINACION_MAX (b2_pi / 2)
#define INCLINACION_MIN (-b2_pi / 2)

class Game;
class Weapon;
class Battlefield;
class Projectile;


class Player: public Entity {
private:
    float life;
    // std::map<WeaponsAndTools,Weapon >Weapons;
    Weapon* weapon;


    bool facing_right;
    bool is_walking;
    bool ready;
    bool is_jumping;
    bool is_backflipping;

    bool aiming;
    float aim_inclination_degrees;  // Radianes
    ADSAngleDir aim_direction;

    bool charging_shoot;
    float weapon_power;

    int facing_factor();

public:
    explicit Player(Battlefield& battlefield);

    void move();
    void stop();
    void jump(const JumpDir& direction);

    void shoot(Game& game);

    void change_aim_direction();
    void change_fire_power();

    void set_ready();
    void check_jumping();

    b2Vec2 set_bullet_direction();
    b2Vec2 set_bullet_power();
    float set_bullet_angle();


    void shoot_aim_weapon(std::shared_ptr<Projectile> projectile);
    // void use_throwable();
    // void use_clickeable_gadget();

    bool is_dead() override;
    void execute_collision_reaction() override;

    virtual ~Player() = default;

    friend class Game;
    friend class BroadCaster;
};

#endif  // PLAYER_H
