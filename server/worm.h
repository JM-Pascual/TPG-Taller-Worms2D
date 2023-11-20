#ifndef WORM_H
#define WORM_H

#include <memory>

#include <box2d/box2d.h>

#include "../common/const.h"

#include "entity.h"

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

class Weapon;
class Projectile;

class Worm: public Entity {
private:
    float life;

    bool facing_right;
    bool is_walking;
    bool is_jumping;
    bool is_backflipping;
    bool falling;

    bool aiming;
    float aim_inclination_degrees;  // Radianes
    ADSAngleDir aim_direction;

    bool charging_shoot;
    float weapon_power;

    std::unique_ptr<Weapon>*& selected_weapon;
    WeaponsAndTools& weapon_type;

    bool was_damaged;

    int facing_factor();

public:
    const uint8_t id;

    explicit Worm(Battlefield& battlefield, std::unique_ptr<Weapon>*& selected_weapon,
                  WeaponsAndTools& type, const uint8_t& id);

    void move();
    void stop();
    void jump(const JumpDir& direction);

    void stop_all();


    void change_aim_direction();
    void change_fire_power();
    void shoot();

    void check_jumping();
    void check_falling();
    void start_falling() override;

    b2Vec2 set_bullet_direction();
    b2Vec2 set_bullet_power();
    float set_bullet_angle();
    uint8_t set_bullet_explosion_delay();

    void recibe_life_modification(const float& life_variation) override;
    void shoot_aim_weapon(std::shared_ptr<Projectile> projectile);
    void use_throwable(std::shared_ptr<Projectile> throwable);
    // void use_clickeable_gadget();

    bool is_dead() override;
    void execute_collision_reaction() override;

    void destroyBody();

    virtual ~Worm() = default;

    friend class Player;
    friend class BroadCaster;
    friend class InfoParser;
    friend class WormHandler;
    friend class TurnHandler;

    Worm(Worm&& o);
};

#endif
