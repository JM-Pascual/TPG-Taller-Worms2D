#ifndef GAMEACTOR_H
#define GAMEACTOR_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common/States.h"
#include "../common/const.h"
#include "box2d/b2_math.h"

#include "Animation.h"
#include "TexturesPool.h"
#include "WeaponAnimation.h"
#include "camera.h"

// ----------------------- ACTOR INTERFACE ----------------------

class GameActor {
protected:
    b2Vec2 position;
    Camera& camera;

public:
    GameActor(const float& x, const float& y, Camera& camera): position(x, y), camera(camera) {}
    virtual void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) = 0;
    virtual void update(std::shared_ptr<States>& actor_state) = 0;
    virtual ~GameActor() = default;
};

// ----------------------- WORM ----------------------

class Worm: public GameActor {
private:
    bool is_walking;
    bool is_jumping;
    bool is_backflipping;
    bool facing_right;
    bool was_hit;

    float aim_inclination_degrees;

    Animation walking;
    Animation jumping;
    Animation backflipping;

    WeaponAnimation weapon_animation;

public:
    Worm(std::shared_ptr<States>& initial_state, TexturesPool& pool, Camera& camera):
            GameActor(std::dynamic_pointer_cast<WormStateG>(initial_state)->pos.x,
                      std::dynamic_pointer_cast<WormStateG>(initial_state)->pos.y, camera),
            is_walking(std::dynamic_pointer_cast<WormStateG>(initial_state)->is_walking),
            is_jumping(std::dynamic_pointer_cast<WormStateG>(initial_state)->is_jumping),
            is_backflipping(std::dynamic_pointer_cast<WormStateG>(initial_state)->is_backflipping),
            facing_right(std::dynamic_pointer_cast<WormStateG>(initial_state)->facing_right),
            was_hit(std::dynamic_pointer_cast<WormStateG>(initial_state)->was_hit),
            aim_inclination_degrees(
                    std::dynamic_pointer_cast<WormStateG>(initial_state)->aim_inclination_degrees),

            walking(pool.get_texture(Actors::WORM), 15, 1),
            jumping(pool.get_texture(Actors::JUMPING_WORM), 5, 5, false),
            backflipping(pool.get_texture(Actors::BACKFLIP_WORM), 22, 1, false),
            weapon_animation(pool) {}

    void update(std::shared_ptr<States>& actor_state) override {
        position = std::dynamic_pointer_cast<WormStateG>(actor_state)->pos;
        is_walking = std::dynamic_pointer_cast<WormStateG>(actor_state)->is_walking;
        is_jumping = std::dynamic_pointer_cast<WormStateG>(actor_state)->is_jumping;
        is_backflipping = std::dynamic_pointer_cast<WormStateG>(actor_state)->is_backflipping;
        facing_right = std::dynamic_pointer_cast<WormStateG>(actor_state)->facing_right;
        was_hit = std::dynamic_pointer_cast<WormStateG>(actor_state)->was_hit;
        aim_inclination_degrees =
                std::dynamic_pointer_cast<WormStateG>(actor_state)->aim_inclination_degrees;

        walking.update(!is_walking);
        jumping.update(!is_jumping);
        backflipping.update(!is_backflipping);

        bool charging_weapon = std::dynamic_pointer_cast<WormStateG>(actor_state)->charging_weapon;
        weapon_animation.update(aim_inclination_degrees, charging_weapon, WeaponsAndTools::BAZOOKA,
                                (is_walking || is_jumping || is_backflipping));
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 32, 60);

        if (is_jumping) {
            jumping.render((*game_renderer), rect, 0, 0,
                           facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        } else if (is_backflipping) {
            backflipping.render((*game_renderer), rect, 0, 0,
                                facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        } else if (is_walking) {
            walking.render((*game_renderer), rect, 0, 0,
                           facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        } else {
            weapon_animation.render((*game_renderer), rect,
                                    facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        }
    }

    ~Worm() override = default;
};


// ----------------------- PROYECTILE INTERFACE ----------------------

class Proyectile: public GameActor {
protected:
    bool impacted;

public:
    Proyectile(std::shared_ptr<States>& initial_state, TexturesPool& pool, Camera& camera):
            GameActor(std::dynamic_pointer_cast<ProjectileStateG>(initial_state)->pos.x,
                      std::dynamic_pointer_cast<ProjectileStateG>(initial_state)->pos.y, camera),
            impacted(false) {}
};


// ----------------------- BAZOOKA PROYECTILE ----------------------

class BazookaProyectile: public Proyectile {
private:
    Animation on_air;
    Animation impact;

public:
    BazookaProyectile(std::shared_ptr<States>& initial_state, TexturesPool& pool, Camera& camera):
            Proyectile(initial_state, pool, camera),
            on_air(pool.get_texture(Actors::BAZOOKA_PROYECTILE), 1, 1),
            impact(pool.get_texture(Actors::BAZOOKA_EXPLOSION), 8, 3, false) {}

    void update(std::shared_ptr<States>& actor_state) override {
        position = std::dynamic_pointer_cast<ProjectileStateG>(actor_state)->pos;
        impacted = std::dynamic_pointer_cast<ProjectileStateG>(actor_state)->impacted;
        impact.update(!impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 60, 60);
        if (impacted) {
            impact.render((*game_renderer), rect);
        } else {
            on_air.render((*game_renderer), rect);
        }
    }
};


#endif  // GAMEACTOR_H
