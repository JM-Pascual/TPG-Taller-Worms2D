#include "cheatmenu.h"

#include "./ui_cheatmenu.h"

#include "Action.h"

CheatMenu::CheatMenu(Queue<std::shared_ptr<Action>>& action_queue, QWidget* parent):
        QDialog(parent), ui(new Ui::CheatMenu), action_queue(action_queue) {
    ui->setupUi(this);
    loadHandlers();
    this->show();
}

void CheatMenu::loadHandlers() {
    connect(ui->ww3Button, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<WW3Cheat>()); });

    connect(ui->madnessButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<RandomKillCheat>()); });

    connect(ui->randomKillButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<InfiniteAmmoCheat>()); });

    connect(ui->infiniteAmmoButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<MadnessCheat>()); });

    connect(ui->infiniteTurnButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<ImmortalWorm>()); });

    connect(ui->inmortalWormButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<MultipleJumpCheat>()); });

    connect(ui->multipleJumpButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<InfiniteTurnCheat>()); });

    connect(ui->everyone1HPButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<Everyone1HPCheat>()); });
}

CheatMenu::~CheatMenu() { delete ui; }
