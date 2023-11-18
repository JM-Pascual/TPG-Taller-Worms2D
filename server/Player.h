#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <map>
#include <memory>

#include <box2d/box2d.h>

#include "../common/const.h"

#include "battlefield.h"
#include "entity.h"
#include "weapon.h"

#define INITIAL_LIFE 100

#define TICK_RATE 30
#define WIDTH 0.9f
#define HEIGHT 1.2f

#define ARM_LENGHT ((WIDTH / 2) + 1)

#define POWER_RAISE 1
#define MAX_POWER 10
#define ANGLE_VARIATION (b2_pi / 64)

#define CATEGORY_BITS 0x002

#define INCLINACION_MAX (b2_pi / 2)
#define INCLINACION_MIN (-b2_pi / 2)

class Game;
class Weapon;
class Battlefield;
class Projectile;


class Player: public Entity {
private:
    float life;
    b2Body* worm;
    // std::map<WeaponsAndTools,Weapon >Weapons;
    Weapon* weapon;


    bool facing_right;
    bool is_walking;
    bool ready;
    bool is_jumping;
    bool is_backflipping;
    bool is_playing;
    bool falling;

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

    void stop_all();


    void change_aim_direction();
    void change_fire_power();

    void set_ready();
    void check_jumping();
    void check_falling();
    void start_falling() override;

    b2Vec2 set_bullet_direction();
    b2Vec2 set_bullet_power();
    float set_bullet_angle();
    uint8_t set_bullet_explosion_delay();

    void recibe_life_modification(float life_variation) override;
    void shoot_aim_weapon(std::shared_ptr<Projectile> projectile);
    void use_throwable(std::shared_ptr<Projectile> throwable);
    // void use_clickeable_gadget();

    bool is_dead() override;
    void execute_collision_reaction() override;

    virtual ~Player() = default;

    friend class Game;
    friend class BroadCaster;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&);
    Player& operator=(Player&&) = delete;
};

#endif  // PLAYER_H
