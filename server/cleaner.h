#ifndef CLEANER_H
#define CLEANER_H

#include <atomic>

#include "../common/thread.h"

class Cleaner: public Thread {

private:
    std::atomic<bool> killed;

public:
    Cleaner();

    void run() override;

    void kill();
};

#endif
