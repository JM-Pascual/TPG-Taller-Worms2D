#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include <SDL2pp/Rect.hh>

#include "../common/config.h"
#include "../common/const.h"

#define _X_ 0
#define _Y_ 1

#define _W_ 0
#define _H_ 1

#define WIDTH 1280.0f
#define HEIGHT 720.0f

#define MAP_WIDTH 1920.0f
#define MAP_HEIGHT 1080.0f

#define MOUSE_MOVEMENT_AMPLIFIER Config::yamlNode["camera_sens"].as<float>()

enum class Priority { NONE, WORM, PROJECTILE };

struct CameraPriority {
public:
    Priority priority;
    uint8_t id;

    CameraPriority(): priority(Priority::NONE), id(0) {}
};

class Camera {
private:
    float position[2];
    float fixed_actor[2];

    void checkBounds();

    void checkMouseBounds();

    void checkActorDimensions(const float& w, const float& h);

public:
    Camera(): position{0, 0}, fixed_actor{0, 0} {}

    void fixActor(const float& x, const float& y, const float& w, const float& h);

    void fixMouse(const float& x, const float& y);

    SDL2pp::Rect calcRect(const float& x, const float& y, const float& w, const float& h);

    SDL2pp::Rect realRect(const float& x, const float& y);

    ~Camera() = default;
};


#endif
