#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QSoundEffect>
#include <QString>
#include <QTimer>
#include <QWidget>
#include <map>
#include <memory>
#include <string>
#include <tuple>
#include <vector>

#include <stdint.h>

#include "client.h"
#include "lobbyListener.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
class GameFrame;
}  // namespace Ui
QT_END_NAMESPACE

class PlayerFrame;
class GameFrame;

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(Client& client, bool& initGame, QWidget* parent = nullptr);

    ~MainWindow();

    void loadIntro();

    void showIntro();

    void loadMenu();

    void showMenu();

    void loadGameSearch();

    void showGameSearch();

    void refreshGameSearch();

    void loadHelp();

    void showHelp();

    void loadLobby();

    void showLobby();

    void lobbyHideAll();

    void startGame();

    void setPlayerFrames();

    friend class GameFrame;
    friend class PlayerFrame;

private:
    Client& client;
    Ui::MainWindow* ui;
    QMovie* movie;
    QMovie* movie_aux;
    QTimer* timer;
    int preHelpIndex;
    bool& initGame;
    QSoundEffect sound;
    QSoundEffect sound_aux;
    std::map<uint8_t, std::unique_ptr<PlayerFrame>> players;
    std::vector<std::unique_ptr<GameFrame>> games;

    std::vector<std::tuple<QLabel*, QPushButton*, QLabel*>> lobby_widgets;


    void validateCreateGame();

    void closeEvent(QCloseEvent* event);
};

#endif  // MAINWINDOW_H
