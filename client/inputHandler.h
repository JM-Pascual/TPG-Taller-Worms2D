#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include <atomic>
#include <memory>

#include <SDL2pp/SDL2pp.hh>

#include "../common/queue.h"
#include "../common/thread.h"

class Action;
class Camera;

class IHandler: public Thread {
private:
    Queue<std::shared_ptr<Action>>& action_queue;
    std::atomic<bool>& quit;
    std::atomic<bool>& my_turn;
    Camera& camera;

    void keyDown(const SDL_Keycode& key);

    void keyUp(const SDL_Keycode& key);

public:
    explicit IHandler(Queue<std::shared_ptr<Action>>& actionQ, std::atomic<bool>& quit,
                      std::atomic<bool>& my_turn, Camera& camera);

    void run() override;

    ~IHandler() = default;
};


#endif
