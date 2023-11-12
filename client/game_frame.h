#ifndef GAME_FRAME_H
#define GAME_FRAME_H

#include <string>

#include <stdint.h>

class QWidget;
class QLabel;
class QHBoxLayout;
class MainWindow;
class QPushButton;


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
    uint8_t game_id;

    explicit GameFrame(QWidget* parent = 0);

    void setFrame(const std::string& descrip, const std::string& map_name,
                  const uint8_t& p_quantity, const uint8_t& game_id);

    void setHandler(MainWindow& w);

    void show();

    ~GameFrame();

    GameFrame(const GameFrame&) = delete;
    GameFrame& operator=(const GameFrame&) = delete;
};


#endif
