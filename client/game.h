#ifndef C_GAME_H
#define C_GAME_H

#include <QApplication>
#include <QThread>
#include <memory>

#include "../common/logger.h"

#include "cheatmenu.h"
#include "client_event_loop.h"
#include "mainwindow.h"

#define HOSTNAME argv[1]
#define SERVNAME argv[2]


class Game {
private:
    std::unique_ptr<QApplication> app;
    std::unique_ptr<MainWindow> window;
    bool initGame;
    std::unique_ptr<CheatMenu> cheat_menu;
    EventLoop client;

public:
    Game(int argc, char* argv[]);

    int run();

    ~Game();
};


#endif
