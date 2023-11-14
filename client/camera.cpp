#include "camera.h"

void Camera::setNewPosition(const float& x, const float& y, const float& w, const float& h) {
    position[X] = x + ((w - WIDTH) / 2);

    // if(position[X] < 0)
    // {
    //     position[X] = 0;

    // } else if (position[X] > MAP_WIDTH - WIDTH)
    // {
    //     position[X] = MAP_WIDTH - WIDTH;
    // }

    position[Y] = y + ((h - HEIGHT) / 2);

    // if(position[Y] < 0)
    // {
    //     position[Y] = 0;
    // } else if( position[Y] > MAP_HEIGHT - HEIGHT )
    // {
    //     position[Y] = MAP_HEIGHT - HEIGHT;
    // }
}

SDL2pp::Rect Camera::calcRect(const float& x, const float& y, const float& w, const float& h) {
    return SDL2pp::Rect(x - ((w / 2) + position[X]), y - ((h / 2) + position[Y]), w, h);
}
