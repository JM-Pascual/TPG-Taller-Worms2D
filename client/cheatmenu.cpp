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

    connect(ui->noWindButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<NoWindCheat>()); });

    connect(ui->infiniteAmmoButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<InfiniteAmmoCheat>()); });

    connect(ui->madnessButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<MadnessCheat>()); });

    connect(ui->inmortalWormButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<ImmortalWorm>()); });

    connect(ui->multipleJumpButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<MultipleJumpCheat>()); });

    connect(ui->infiniteTurnButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<InfiniteTurnCheat>()); });

    connect(ui->everyone1HPButton, &QPushButton::clicked, this,
            [this]() { this->action_queue.push(std::make_shared<Everyone1HPCheat>()); });
}

CheatMenu::~CheatMenu() { delete ui; }
