#ifndef WORM_H
#define WORM_H

#include <memory>

#include <box2d/box2d.h>

#include "../common/config.h"
#include "../common/const.h"

#include "entity.h"

#define INITIAL_LIFE Config::yamlNode["initial_life"].as<int>()

#define TICK_RATE Config::yamlNode["tick_rate"].as<int>()

#define WIDTH Config::yamlNode["worm_width"].as<float>()
#define HEIGHT Config::yamlNode["worm_height"].as<float>()

#define ARM_LENGHT Config::yamlNode["arm_length"].as<float>()

#define POWER_RAISE Config::yamlNode["power_raise"].as<int>()
#define MAX_POWER Config::yamlNode["max_power"].as<int>()
#define ANGLE_VARIATION (b2_pi / 64)

#define CATEGORY_BITS 0x002

#define INCLINACION_MAX (b2_pi / 2)
#define INCLINACION_MIN (-b2_pi / 2)

#define MIN_SQUARED_VELOCITY 0.0001
#define MIN_Y_VELOCITY 0.001

#define MIN_FALLING_DAMAGE_HEIGHT Config::yamlNode["min_falling_damage"].as<float>()
#define MAX_FALLING_DAMAGE Config::yamlNode["max_falling_damage"].as<float>()
#define FALL_DMG_AMP Config::yamlNode["fall_damage_amplification"].as<int>()

class Gadget;
class Projectile;

class Worm: public Entity {
private:
    float life;

    bool facing_right;
    bool is_walking;
    bool is_jumping;
    bool is_backflipping;
    bool falling;
    bool using_tool;

    bool aiming;
    float aim_inclination_degrees;  // Radianes
    ADSAngleDir aim_direction;

    bool charging_shoot;
    float weapon_power;

    DelayAmount weapon_delay;
    b2Vec2 clicked_position;

    std::unique_ptr<Gadget>*& selected_weapon;
    WeaponsAndTools& weapon_type;

    bool was_damaged;

    float pos_y_before_falling;
    const bool& allow_multiple_jump;
    const bool& immortal_worms;


    int facing_factor();

public:
    const uint8_t id;

    explicit Worm(Battlefield& battlefield, std::unique_ptr<Gadget>*& selected_weapon,
                  WeaponsAndTools& type, const uint8_t& id, const bool& allow_multiple_jump,
                  const bool& immortal_worms);

    void move();
    void stop();
    void jump(const JumpDir& direction);

    void stop_all();


    b2Vec2 set_bullet_direction();
    b2Vec2 set_bullet_power();
    b2Vec2 set_bullet_angle();
    void change_bullet_explosion_delay(DelayAmount delay);
    void change_clicked_position(b2Vec2 new_position);

    void change_aim_direction();
    void change_fire_power();
    void shoot();

    void stop_falling() override;
    void start_falling() override;


    void recibe_life_modification(const float& life_variation) override;
    void use_chargeable_weapon(const std::shared_ptr<Projectile>& projectile);
    void use_positional_weapon(const std::shared_ptr<Projectile>& throwable);


    void change_position();
    b2Vec2 clicked_position_();
    DelayAmount grenade_explosion_delay();

    bool is_dead() override;
    void collision_reaction() override;

    void destroyBody();

    void applyWindResistance(const float& wind_force) override;

    b2Vec2 position();

    float distance_to_body(b2Body* body_);
    b2Vec2 forward_bound(b2Vec2 bound);
    b2Vec2 backward_bound(b2Vec2 bound);

    bool is_facing_right();

    virtual ~Worm() = default;

    friend class Player;
    friend class BroadCaster;
    friend class InfoParser;
    friend class WormHandler;
    friend class TurnHandler;

    Worm(Worm&& o);
};

#endif
