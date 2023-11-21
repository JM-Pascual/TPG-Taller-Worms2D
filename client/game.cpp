#include "game.h"


Game::Game(int argc, char* argv[]):
        initGame(false),
        appRet(0),
        client(HOSTNAME, SERVNAME),
        app(std::make_unique<QApplication>(argc, argv)),
        window(std::make_unique<MainWindow>(client, initGame)) {}

int Game::run() {
    window->show();
    int ret = app->exec();

    if (ret != 0) {
        return ret;
    }

    if (initGame) {
        // window ya esta cerrado si el thread esta aca
        window = nullptr;
        app->exit(ret);
        app = nullptr;
        client.run();
    }

    return appRet;
}
