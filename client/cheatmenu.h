#ifndef CHEATMENU_H
#define CHEATMENU_H

#include <QApplication>
#include <QDialog>
#include <QSoundEffect>
#include <memory>

#include "../common/queue.h"

class Action;

QT_BEGIN_NAMESPACE
namespace Ui {
class CheatMenu;
}
QT_END_NAMESPACE

class CheatMenu: public QDialog {
    Q_OBJECT

public:
    explicit CheatMenu(Queue<std::shared_ptr<Action>>& action_queue, QWidget* parent = nullptr);
    ~CheatMenu();

private:
    Ui::CheatMenu* ui;
    Queue<std::shared_ptr<Action>>& action_queue;
    QSoundEffect button_sound;

    void loadHandlers();
};

#endif  // CHEATMENU_H
