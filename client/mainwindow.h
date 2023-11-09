#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QTimer>
#include <QWidget>
#include <atomic>
#include <memory>
#include <string>
#include <vector>

#include <stdint.h>

#include "client.h"
#include "cparser.h"

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
    explicit MainWindow(const char* hostname, const char* servname, QWidget* parent = nullptr);

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


    friend class GameFrame;
    friend class PlayerFrame;

private:
    Client client;

    Ui::MainWindow* ui;
    QMovie* movie;
    QMovie* movie_aux;
    QTimer* timer;
    std::vector<std::unique_ptr<PlayerFrame>> players;
    std::vector<std::unique_ptr<GameFrame>> games;
};

class GameFrame {
public:
    QWidget* frame;

private:
    QHBoxLayout* layout;
    QLabel* description;
    QLabel* map;
    QLabel* players;
    QPushButton* joinGame;

public:
    explicit GameFrame(QWidget* parent = 0);

    void setFrame(const std::string& descrip, const std::string& map_name,
                  const uint8_t& p_quantity, const uint8_t& game_id);

    void setHandler(MainWindow& w);

    void show();

    ~GameFrame();

    GameFrame(const GameFrame&) = delete;
    GameFrame& operator=(const GameFrame&) = delete;
};

class PlayerFrame {
private:
    QLabel* character_label;
    QPushButton* ready_button;
    QLabel* player_id;

public:
    explicit PlayerFrame(QLabel* label, QPushButton* button, QLabel* id_label,
                         const uint8_t& player_id):
            character_label(label), ready_button(button), player_id(id_label) {
        this->hide();
        // cppcheck-suppress danglingTemporaryLifetime
        QString lblTxt = std::string("Player ID: " + std::to_string(player_id)).data();
        // cppcheck-suppress danglingTemporaryLifetime
        id_label->setText(lblTxt);
    }

    void hide();

    void ready();

    void show();

    ~PlayerFrame() = default;
};

#endif  // MAINWINDOW_H
