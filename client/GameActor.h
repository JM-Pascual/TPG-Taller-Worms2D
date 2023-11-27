#ifndef GAMEACTOR_H
#define GAMEACTOR_H

#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common/States.h"
#include "../common/const.h"
#include "box2d/b2_math.h"

#include "Animation.h"
#include "TexturesPool.h"
#include "WeaponAnimationHolder.h"
#include "ToolAnimationHolder.h"
#include "camera.h"
#include "death_animation.h"
#include "text_printer.h"

// ----------------------- ACTOR INTERFACE ----------------------

class GameActor {
protected:
    b2Vec2 position;
    Camera& camera;

public:
    GameActor(const float& x, const float& y, Camera& camera): position(x, y), camera(camera) {}
    virtual void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) = 0;
    virtual void update(std::shared_ptr<States>& actor_state) = 0;
    virtual void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                             TextPrinter& state_printer) = 0;
    virtual ~GameActor() = default;
};

// ----------------------- WORM ----------------------

class Worm: public GameActor {
private:
    WeaponsAndTools equipped_weapon;
    bool on_turn_time;
    bool is_walking;
    bool is_jumping;
    bool is_backflipping;
    bool facing_right;
    bool was_hit;
    bool using_tool;
    float life_points_remaining;

    float aim_inclination_degrees;

    Animation walking;
    Animation jumping;
    Animation backflipping;

    DeathAnimation dead;

    WeaponAnimationHolder weapon_animations;

    ToolAnimationHolder tool_usage_animations;

public:
    Worm(std::shared_ptr<WormStateG>& initial_state, TexturesPool& pool, Camera& camera):
            GameActor(initial_state->pos.x, initial_state->pos.y, camera),
            equipped_weapon(initial_state->weapon),
            on_turn_time(initial_state->on_turn_time),
            is_walking(initial_state->is_walking),
            is_jumping(initial_state->is_jumping),
            is_backflipping(initial_state->is_backflipping),
            facing_right(initial_state->facing_right),
            was_hit(initial_state->was_hit),
            using_tool(initial_state->using_tool),
            life_points_remaining(initial_state->life),
            aim_inclination_degrees(initial_state->aim_inclination_degrees),

            walking(pool.get_actor_texture(Actors::WORM), 15, 1),
            jumping(pool.get_actor_texture(Actors::JUMPING_WORM), 5, 5, false),
            backflipping(pool.get_actor_texture(Actors::BACKFLIP_WORM), 22, 1, false),
            dead(pool, 0),
            weapon_animations(pool),
            tool_usage_animations(pool){}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<WormStateG>(actor_state);
        position = state->pos;
        on_turn_time = state->on_turn_time;
        equipped_weapon = state->weapon;
        is_walking = state->is_walking;
        is_jumping = state->is_jumping;
        is_backflipping = state->is_backflipping;
        facing_right = state->facing_right;
        was_hit = state->was_hit;
        using_tool = state->using_tool;
        aim_inclination_degrees = state->aim_inclination_degrees;
        life_points_remaining = state->life;

        walking.update(!is_walking);
        jumping.update(!is_jumping);
        backflipping.update(!is_backflipping);
        dead.update((life_points_remaining > 0));

        bool charging_weapon = state->charging_weapon;

        weapon_animations.update(aim_inclination_degrees, charging_weapon, equipped_weapon,
                                (is_walking || is_jumping || is_backflipping));
        tool_usage_animations.update(state);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect render_rect = camera.calcRect(position.x, position.y, 32, 60);

        if (life_points_remaining == 0) {
            SDL2pp::Rect death_render_rect = camera.calcRect(position.x, position.y, 60, 60);
            dead.render((*game_renderer), death_render_rect);
            return;
        }

        if (on_turn_time) {
            if (is_jumping) {
                jumping.render((*game_renderer), render_rect, 0, 0,
                               facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
            } else if (is_backflipping) {
                backflipping.render((*game_renderer), render_rect, 0, 0,
                                    facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
            } else if (is_walking) {
                walking.render((*game_renderer), render_rect, 0, 0,
                               facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
            } else if (using_tool){
                tool_usage_animations.render((*game_renderer), camera, 0, 0,
                                             facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
            }
            else {
                weapon_animations.render((*game_renderer), render_rect,
                                        facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
            }
        } else {
            walking.render((*game_renderer), render_rect, 0, 0,
                           facing_right ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        }
    }


    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {
        if (!on_turn_time) {
            SDL2pp::Rect render_rect = camera.calcRect(position.x, position.y, 32, 60);
            state_printer.print_text((*game_renderer), std::to_string(int(life_points_remaining)),
                                     render_rect.x + 8, render_rect.y - 30, true);
        }
    }

    ~Worm() override = default;
};


// ----------------------- PROYECTILE INTERFACE ----------------------

class Projectile: public GameActor {
protected:
    bool impacted;

public:
    Projectile(std::shared_ptr<ProjectileStateG>& initial_state, TexturesPool& pool,
               Camera& camera):
            GameActor(initial_state->pos.x, initial_state->pos.y, camera), impacted(false) {}
};


// ----------------------- BAZOOKA PROYECTILE ----------------------

class BazookaProjectile: public Projectile {
private:
    Animation on_air;
    Animation impact;

    float current_angle;

public:
    BazookaProjectile(std::shared_ptr<ProjectileStateG>& initial_state, TexturesPool& pool,
                      Camera& camera):
            Projectile(initial_state, pool, camera),
            on_air(pool.get_projectile_texture(Projectiles::BAZOOKA_PROYECTILE), 1, 1),
            impact(pool.get_effect_texture(Effects::NORMAL_EXPLOSION), 8, 3, false),
            current_angle(0) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<ProjectileStateG>(actor_state);
        position = state->pos;
        impacted = state->impacted;
        current_angle = state->angle;
        impact.update(!impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 60, 60);
        if (impacted) {
            impact.render((*game_renderer), rect);
        } else {
            on_air.render((*game_renderer), rect, 0, 0, SDL_FLIP_NONE,
                          (-1 * (current_angle * 180) / M_PI));
        }
    }

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- MORTAR PROYECTILE ----------------------

class MortarProjectile: public Projectile {
private:
    Animation on_air;
    Animation impact;

    float current_angle;

public:
    MortarProjectile(std::shared_ptr<ProjectileStateG>& initial_state, TexturesPool& pool,
                     Camera& camera):
            Projectile(initial_state, pool, camera),
            on_air(pool.get_projectile_texture(Projectiles::MORTAR_PROYECTILE), 1, 1),
            impact(pool.get_effect_texture(Effects::NORMAL_EXPLOSION), 8, 3, false),
            current_angle(0) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<ProjectileStateG>(actor_state);
        position = state->pos;
        impacted = state->impacted;
        current_angle = state->angle;
        impact.update(!impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 60, 60);
        if (impacted) {
            impact.render((*game_renderer), rect);
        } else {
            on_air.render((*game_renderer), rect, 0, 0, SDL_FLIP_NONE,
                          (-1 * (current_angle * 180) / M_PI));
        }
    }

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- MORTAR FRAGMENT ----------------------

class MortarFragment: public Projectile {
private:
    Animation on_air;
    Animation impact;

    float current_angle;

public:
    MortarFragment(std::shared_ptr<ProjectileStateG>& initial_state, TexturesPool& pool,
                   Camera& camera):
            Projectile(initial_state, pool, camera),
            on_air(pool.get_projectile_texture(Projectiles::MORTAR_FRAGMENT), 6, 1, true),
            impact(pool.get_effect_texture(Effects::FRAGMENT_EXPLOSION), 11, 1, false),
            current_angle(0) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<ProjectileStateG>(actor_state);
        position = state->pos;
        impacted = state->impacted;
        current_angle = state->angle;
        impact.update(!impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 60, 60);
        if (impacted) {
            impact.render((*game_renderer), rect);
        } else {
            on_air.render((*game_renderer), rect, 0, 0, SDL_FLIP_NONE,
                          (-1 * (current_angle * 180) / M_PI));
        }
    }

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- GREEN GRENADE ----------------------

class GreenGrenadeProjectile: public Projectile {
private:
    Animation on_air;
    Animation impact;

    float current_angle;

public:
    GreenGrenadeProjectile(std::shared_ptr<ProjectileStateG>& initial_state, TexturesPool& pool,
                           Camera& camera):
            Projectile(initial_state, pool, camera),
            on_air(pool.get_projectile_texture(Projectiles::GREEN_GRENADE_PROYECTILE), 1, 1),
            impact(pool.get_effect_texture(Effects::NORMAL_EXPLOSION), 8, 3, false),
            current_angle(0) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<ProjectileStateG>(actor_state);
        position = state->pos;
        impacted = state->impacted;
        current_angle = state->angle;
        impact.update(!impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 60, 60);
        if (impacted) {
            impact.render((*game_renderer), rect);
        } else {
            on_air.render((*game_renderer), rect, 0, 0, SDL_FLIP_NONE,
                          (-1 * (current_angle * 180) / M_PI));
        }
    }

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- RED GRENADE ----------------------

class RedGrenadeProjectile: public Projectile {
private:
    Animation on_air;
    Animation impact;

    float current_angle;

public:
    RedGrenadeProjectile(std::shared_ptr<ProjectileStateG>& initial_state, TexturesPool& pool,
                         Camera& camera):
            Projectile(initial_state, pool, camera),
            on_air(pool.get_projectile_texture(Projectiles::RED_GRENADE_PROYECTILE), 1, 1),
            impact(pool.get_effect_texture(Effects::NORMAL_EXPLOSION), 8, 3, false),
            current_angle(0) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<ProjectileStateG>(actor_state);
        position = state->pos;
        impacted = state->impacted;
        current_angle = state->angle;
        impact.update(!impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 60, 60);
        if (impacted) {
            impact.render((*game_renderer), rect);
        } else {
            on_air.render((*game_renderer), rect, 0, 0, SDL_FLIP_NONE,
                          (-1 * (current_angle * 180) / M_PI));
        }
    }

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- BANANA ----------------------

class BananaProjectile: public Projectile {
private:
    Animation on_air;
    Animation impact;

    float current_angle;

public:
    BananaProjectile(std::shared_ptr<ProjectileStateG>& initial_state, TexturesPool& pool,
                     Camera& camera):
            Projectile(initial_state, pool, camera),
            on_air(pool.get_projectile_texture(Projectiles::BANANA_PROYECTILE), 1, 1),
            impact(pool.get_effect_texture(Effects::NORMAL_EXPLOSION), 8, 3, false),
            current_angle(0) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<ProjectileStateG>(actor_state);
        position = state->pos;
        impacted = state->impacted;
        current_angle = state->angle;
        impact.update(!impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 60, 60);
        if (impacted) {
            impact.render((*game_renderer), rect);
        } else {
            on_air.render((*game_renderer), rect, 0, 0, SDL_FLIP_NONE,
                          (-1 * (current_angle * 180) / M_PI));
        }
    }

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- DYNAMITE ----------------------

class DynamiteProjectile: public Projectile {
private:
    Animation countdown;
    Animation explosion;

public:
    DynamiteProjectile(std::shared_ptr<ProjectileStateG>& initial_state, TexturesPool& pool,
                       Camera& camera):
            Projectile(initial_state, pool, camera),
            countdown(pool.get_projectile_texture(Projectiles::DYNAMITE_PROYECTILE), 126),
            explosion(pool.get_effect_texture(Effects::NORMAL_EXPLOSION), 8, 3, false) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<ProjectileStateG>(actor_state);
        position = state->pos;
        countdown.update();
        impacted = state->impacted;
        explosion.update(!impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 60, 60);
        if (impacted) {
            explosion.render((*game_renderer), rect);
        } else {
            countdown.render((*game_renderer), rect);
        }
    }

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- AIR STRIKE ----------------------

class AirStrikeProjectile: public Projectile {
private:
    Animation on_air;
    Animation impact;

    float current_angle;
public:
    AirStrikeProjectile(std::shared_ptr<ProjectileStateG>& initial_state, TexturesPool& pool,
                     Camera& camera):
            Projectile(initial_state, pool, camera),
            on_air(pool.get_projectile_texture(Projectiles::AIR_STRIKE_PROYECTILE), 1, 1),
            impact(pool.get_effect_texture(Effects::NORMAL_EXPLOSION), 8, 3, false),
            current_angle(0) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<ProjectileStateG>(actor_state);
        position = state->pos;
        impacted = state->impacted;
        current_angle = state->angle;
        impact.update(!impacted);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        SDL2pp::Rect rect = camera.calcRect(position.x, position.y, 60, 60);
        if (impacted) {
            impact.render((*game_renderer), rect);
        } else {
            on_air.render((*game_renderer), rect, 0, 0, SDL_FLIP_NONE,
                          (-1 * (current_angle * 180) / M_PI));
        }
    }

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- CRATE INTERFACE ----------------------

class Crate: public GameActor {
protected:
    Animation falling;
    Animation on_floor;

    bool still_falling;
    bool was_opened;

public:
    Crate(std::shared_ptr<CrateState>& initial_state, TexturesPool& pool, Camera& camera):
            GameActor(initial_state->pos.x, initial_state->pos.y, camera),
            falling(pool.get_level_texture(TerrainActors::CRATE_FALLING), 27, 2, true),
            on_floor(pool.get_level_texture(TerrainActors::CRATE), 15, 1, false),
            still_falling(true),
            was_opened(false) {}

    void print_state(std::shared_ptr<SDL2pp::Renderer>& game_renderer,
                     TextPrinter& state_printer) override {}
};

// ----------------------- TRAP CRATE ----------------------

class TrapCrate: public Crate {
private:
    Animation opening;

public:
    TrapCrate(std::shared_ptr<CrateState>& initial_state, TexturesPool& pool, Camera& camera):
            Crate(initial_state, pool, camera),
            opening(pool.get_effect_texture(Effects::NORMAL_EXPLOSION), 8, 3, false) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<CrateState>(actor_state);
        position = state->pos;
        still_falling = state->falling;
        was_opened = state->was_opened;
        falling.update(!still_falling);
        on_floor.update(still_falling);
        opening.update(!was_opened);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (still_falling) {
            SDL2pp::Rect rect_falling = camera.calcRect(position.x, position.y, 70, 74);
            falling.render((*game_renderer), rect_falling, 0, 0, SDL_FLIP_NONE);
        } else if (was_opened) {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, position.y, 60, 60);
            opening.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        } else {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, position.y, 60, 60);
            on_floor.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        }
    }
};

class HealCrate: public Crate {
private:
    Animation opening;

public:
    HealCrate(std::shared_ptr<CrateState>& initial_state, TexturesPool& pool, Camera& camera):
            Crate(initial_state, pool, camera),
            opening(pool.get_effect_texture(Effects::CRATE_HEAL), 13, 2, false) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<CrateState>(actor_state);
        position = state->pos;
        still_falling = state->falling;
        was_opened = state->was_opened;
        falling.update(!still_falling);
        on_floor.update(still_falling);
        opening.update(!was_opened);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (still_falling) {
            SDL2pp::Rect rect_falling = camera.calcRect(position.x, position.y, 70, 74);
            falling.render((*game_renderer), rect_falling, 0, 0, SDL_FLIP_NONE);
        } else if (was_opened) {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, (position.y - 30), 60, 60);
            opening.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        } else {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, position.y, 60, 60);
            on_floor.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        }
    }
};

class AmmoCrate: public Crate {
private:
    Animation opening;

public:
    AmmoCrate(std::shared_ptr<CrateState>& initial_state, TexturesPool& pool, Camera& camera):
            Crate(initial_state, pool, camera),
            opening(pool.get_effect_texture(Effects::CRATE_AMMO), 21, 2, false) {}

    void update(std::shared_ptr<States>& actor_state) override {
        auto state = std::dynamic_pointer_cast<CrateState>(actor_state);
        position = state->pos;
        still_falling = state->falling;
        was_opened = state->was_opened;
        falling.update(!still_falling);
        on_floor.update(still_falling);
        opening.update(!was_opened);
    }

    void render(std::shared_ptr<SDL2pp::Renderer>& game_renderer) override {
        if (still_falling) {
            SDL2pp::Rect rect_falling = camera.calcRect(position.x, position.y, 70, 74);
            falling.render((*game_renderer), rect_falling, 0, 0, SDL_FLIP_NONE);
        } else if (was_opened) {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, (position.y - 30), 60, 60);
            opening.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        } else {
            SDL2pp::Rect rect_floor = camera.calcRect(position.x, position.y, 60, 60);
            on_floor.render((*game_renderer), rect_floor, 0, 0, SDL_FLIP_NONE);
        }
    }
};

#endif  // GAMEACTOR_H
