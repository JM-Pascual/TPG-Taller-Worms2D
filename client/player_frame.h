#ifndef PLAYER_FRAME_H
#define PLAYER_FRAME_H

#include <stdint.h>

class QLabel;
class QPushButton;

class PlayerFrame {
private:
    QLabel* character_label;
    QPushButton* ready_button;
    QLabel* player_id;

public:
    const uint8_t id;
    const bool ready_state;

    explicit PlayerFrame(const uint8_t& player_id, const bool& ready);

    void hide();

    void setFrame(QLabel* label, QPushButton* button, QLabel* id_label);

    void ready();

    void show();

    ~PlayerFrame() = default;
};


#endif
