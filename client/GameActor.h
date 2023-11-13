#ifndef GAMEACTOR_H
#define GAMEACTOR_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common/States.h"
#include "../common/const.h"
#include "box2d/b2_math.h"

#include "Animation.h"
#include "TexturesPool.h"

// ----------------------- ACTOR INTERFACE ----------------------

class GameActor {
protected:
    b2Vec2 position;

public:
    GameActor(const float& x, const float& y): position(x, y) {}
    virtual void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) = 0;
    virtual void update(const std::shared_ptr<States>& actor_state, unsigned int ms) = 0;
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

public:
    Worm(const std::shared_ptr<States>& initial_state, TexturesPool& pool):
            GameActor(std::dynamic_pointer_cast<PlayerStateG>(initial_state)->pos.x,
                      std::dynamic_pointer_cast<PlayerStateG>(initial_state)->pos.y),
            is_walking(std::dynamic_pointer_cast<PlayerStateG>(initial_state)->is_walking),
            is_jumping(std::dynamic_pointer_cast<PlayerStateG>(initial_state)->is_jumping),
            is_backflipping(
                    std::dynamic_pointer_cast<PlayerStateG>(initial_state)->is_backflipping),
            facing_right(std::dynamic_pointer_cast<PlayerStateG>(initial_state)->facing_right),
            was_hit(std::dynamic_pointer_cast<PlayerStateG>(initial_state)->was_hit),
            aim_inclination_degrees(std::dynamic_pointer_cast<PlayerStateG>(initial_state)
                                            ->aim_inclination_degrees),
            walking(pool.get_texture(Actors::WORM), 15, 1),
            jumping(pool.get_texture(Actors::JUMPING_WORM), 5, 5, false),
            backflipping(pool.get_texture(Actors::BACKFLIP_WORM), 22, 1, false){}

    void update(const std::shared_ptr<States>& actor_state, unsigned int ms) override {
        position = std::dynamic_pointer_cast<PlayerStateG>(actor_state)->pos;
        is_walking = std::dynamic_pointer_cast<PlayerStateG>(actor_state)->is_walking;
        is_jumping = std::dynamic_pointer_cast<PlayerStateG>(actor_state)->is_jumping;
        is_backflipping = std::dynamic_pointer_cast<PlayerStateG>(actor_state)->is_backflipping;
        facing_right = std::dynamic_pointer_cast<PlayerStateG>(actor_state)->facing_right;
        was_hit = std::dynamic_pointer_cast<PlayerStateG>(actor_state)->was_hit;
        aim_inclination_degrees =
                std::dynamic_pointer_cast<PlayerStateG>(actor_state)->aim_inclination_degrees;

        walking.update(!is_walking);
        jumping.update(!is_jumping);
        backflipping.update(!is_backflipping);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (is_jumping) {
            jumping.render((*game_renderer), SDL2pp::Rect(position.x, position.y, 32, 60), 0, 0,
                           facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        } else if (is_backflipping) {
            backflipping.render((*game_renderer), SDL2pp::Rect(position.x, position.y, 32, 60), 0,
                                0, facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        } else {
            walking.render((*game_renderer), SDL2pp::Rect(position.x, position.y, 32, 60), 0, 0,
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
    Proyectile(const std::shared_ptr<States>& initial_state, TexturesPool& pool):
            GameActor(std::dynamic_pointer_cast<ProjectileStateG>(initial_state)->pos.x,
                      std::dynamic_pointer_cast<ProjectileStateG>(initial_state)->pos.y),
            impacted(false) {}
};


// ----------------------- BAZOOKA PROYECTILE ----------------------

class BazookaProyectile: public Proyectile {
private:
    Animation on_air;
    Animation impact;

public:
    BazookaProyectile(const std::shared_ptr<States>& initial_state, TexturesPool& pool):
            Proyectile(initial_state, pool),
            on_air(pool.get_texture(Actors::BAZOOKA_PROYECTILE), 1, 1),
            impact(pool.get_texture(Actors::BAZOOKA_EXPLOSION), 7, 1, false) {}

    void update(const std::shared_ptr<States>& actor_state, unsigned int ms) override {
        position = std::dynamic_pointer_cast<ProjectileStateG>(actor_state)->pos;
        impacted = std::dynamic_pointer_cast<ProjectileStateG>(actor_state)->impacted;
        on_air.update(!impacted);
        impact.update(impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (impacted) {
            impact.render((*game_renderer), SDL2pp::Rect(position.x, position.y, 60, 60));
        } else {
            on_air.render((*game_renderer), SDL2pp::Rect(position.x, position.y, 60, 60));
        }
    }
};


#endif  // GAMEACTOR_H
