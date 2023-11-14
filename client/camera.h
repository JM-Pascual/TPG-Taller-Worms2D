#ifndef CAMERA_H
#define CAMERA_H

#include <memory>

#include <SDL2pp/Rect.hh>

#define X 0
#define Y 1
#define WIDTH 1280.0f
#define HEIGHT 720.0f

#define MAP_WIDTH 1280
#define MAP_HEIGHT 720

class Camera {
private:
    float position[2];

public:
    Camera(): position{0, 0} {}

    void setNewPosition(const float& x, const float& y, const float& w, const float& h);

    SDL2pp::Rect calcRect(const float& x, const float& y, const float& w, const float& h);
};


#endif
