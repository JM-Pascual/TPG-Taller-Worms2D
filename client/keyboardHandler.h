#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include "../common/queue.h"
#include "../common/thread.h"
#include <atomic>

class Action;

class KBHandler : public Thread {
private:
    Queue<std::shared_ptr<Action>>& action_queue;
    std::atomic<bool>& quit;

public:
    explicit KBHandler(Queue<std::shared_ptr<Action>>& actionQ, std::atomic<bool>& quit);

    void run() override;

    ~KBHandler() = default;

};



#endif
