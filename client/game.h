#ifndef C_GAME_H
#define C_GAME_H

#include <QApplication>
#include <memory>

#include "../common/logger.h"

#include "client_event_loop.h"
#include "mainwindow.h"

#define HOSTNAME argv[1]
#define SERVNAME argv[2]

class Game {
private:
    bool initGame;
    int appRet;
    EventLoop client;
    std::unique_ptr<QApplication> app;
    std::unique_ptr<MainWindow> window;

public:
    Game(int argc, char* argv[]);

    int run();

    ~Game() = default;
};


#endif
