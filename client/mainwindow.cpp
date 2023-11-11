#include "mainwindow.h"

#include <QFrame>
#include <QLabel>
#include <QLayout>
#include <QMovie>
#include <QPalette>
#include <QPushButton>
#include <QSizePolicy>
#include <QTimer>

#include <qmovie.h>

#include "../common/const.h"
#include "./ui_mainwindow.h"

#include "cparser.h"


MainWindow::MainWindow(Client& client, bool& initGame, QWidget* parent):
        QMainWindow(parent),
        client(client),
        ui(new Ui::MainWindow),
        movie(new QMovie("./client/resources/images/intro.gif")),
        movie_aux(new QMovie("./client/resources/images/explosion.gif")),
        timer(new QTimer()),
        preHelpIndex((int)SWIndex::MENU),
        initGame(initGame) {
    ui->setupUi(this);
    // Cambiar icono ventana
    QIcon icon("./client/resources/images/icon.png");
    this->setWindowIcon(icon);
    // Tamanio ventana
    this->setMaximumSize(1280, 720);
    this->setMinimumSize(1280, 720);

    this->loadIntro();
    this->loadMenu();
    this->loadGameSearch();
    this->loadHelp();
    this->loadLobby();
    this->showIntro();
}

void MainWindow::loadIntro() {
    ui->titleIntro_label->hide();

    ui->movieIntro->setScaledContents(true);
    ui->movieIntro->setLineWidth(0);
    ui->movieIntro->setMargin(0);
    ui->movieIntro->setGeometry(0, 0, this->width(), this->height());
    ui->movieIntro->lower();
    ui->movieIntro->setBackgroundRole(QPalette::Window);
    ui->movieIntro->show();

    ui->explosionMovie->setScaledContents(true);
    ui->explosionMovie->setLineWidth(0);
    ui->explosionMovie->setMargin(0);
    ui->explosionMovie->setGeometry(-700, -500, this->width() * 2, this->height() * 2);
    ui->explosionMovie->raise();
    ui->explosionMovie->setBackgroundRole(QPalette::Window);
    ui->explosionMovie->hide();

    ui->titleIntro_label->setGeometry((this->width() - 499) / 2, (this->height() - 266) / 2, 499,
                                      266);

    ui->skipbutton->raise();
    ui->skipbutton->setStyleSheet("QPushButton { background-color: transparent; border: 0px }");

    ui->skipLabel->setGeometry((this->width() - 700) / 2, 580, 700, 100);

    timer->setInterval(1500);

    connect(timer, &QTimer::timeout, this, [this]() {
        ui->explosionMovie->show();
        movie_aux->start();
        timer->stop();
    });

    connect(ui->skipbutton, &QPushButton::clicked, this, [this]() {
        movie->stop();
        movie_aux->stop();
        timer->stop();
        showMenu();
    });

    connect(movie, &QMovie::frameChanged, this, [this]() {
        if (movie->currentFrameNumber() == (movie->frameCount() - 1)) {
            movie->stop();
            if (movie->state() == QMovie::NotRunning) {
                emit movie->finished();
            }
            ui->titleIntro_label->show();
            timer->start();
        }
    });

    connect(movie_aux, &QMovie::frameChanged, this, [this]() {
        if (movie_aux->currentFrameNumber() == (movie_aux->frameCount() - 1)) {
            movie_aux->stop();
            if (movie_aux->state() == QMovie::NotRunning) {
                emit movie_aux->finished();
            }
            showMenu();
        }
    });
}

void MainWindow::showIntro() {
    ui->menuScreens->setCurrentIndex((int)SWIndex::INTRO);

    ui->movieIntro->setMovie(movie);
    movie->start();

    ui->explosionMovie->setMovie(movie_aux);
}

void MainWindow::loadMenu() {
    ui->movieLabel->setScaledContents(true);
    ui->movieLabel->setLineWidth(0);
    ui->movieLabel->setMargin(0);
    ui->movieLabel->setGeometry(0, 0, this->width(), this->height());
    ui->movieLabel->lower();
    ui->movieLabel->setBackgroundRole(QPalette::Window);
    ui->movieLabel->show();

    connect(ui->browseButton, &QPushButton::clicked, this, [this]() { showGameSearch(); });

    connect(ui->helpButton, &QPushButton::clicked, this, [this]() { this->showHelp(); });

    connect(ui->exitButton, &QPushButton::clicked, this, [this]() { this->close(); });
}

void MainWindow::showMenu() {
    ui->menuScreens->setCurrentIndex((int)SWIndex::MENU);
    if (movie) {
        delete movie;
    }
    movie = new QMovie("./client/resources/images/star.gif");
    ui->movieLabel->setMovie(movie);
    movie->start();
}

void MainWindow::loadGameSearch() {
    ui->searchMovie->setScaledContents(true);
    ui->searchMovie->setLineWidth(0);
    ui->searchMovie->setMargin(0);
    ui->searchMovie->setGeometry(0, 0, this->width(), this->height());
    ui->searchMovie->lower();
    ui->searchMovie->setBackgroundRole(QPalette::Window);
    ui->searchMovie->show();

    connect(ui->goMenu_button, &QPushButton::clicked, this, [this]() {
        games.clear();
        this->showMenu();
    });

    connect(ui->help_button, &QPushButton::clicked, this, [this]() { this->showHelp(); });

    connect(ui->refresh_button, &QPushButton::clicked, this,
            [this]() { this->refreshGameSearch(); });

    // Create menu

    ui->createMenu->lower();

    QStringList list = (QStringList() << "Sea"
                                      << "Inferno"
                                      << "Heaven"
                                      << "Mansion");
    ui->map_cbox->addItems(list);
    ui->map_cbox->setCurrentIndex(-1);

    connect(ui->create_button, &QPushButton::clicked, this,
            [this]() { this->ui->createMenu->raise(); });

    connect(ui->goback_button_3, &QPushButton::clicked, this, [this]() {
        this->ui->createMenu->lower();
        ui->desc_txtbox->clear();
        ui->map_cbox->setCurrentIndex(-1);
        ui->create_map_label->setStyleSheet("color: black;");
        ui->create_desc_label->setStyleSheet("color: black;");
    });

    connect(
            ui->createGame_button_2, &QPushButton::clicked, this,
            [this]() { this->validateCreateGame(); }, Qt::QueuedConnection);
}

void MainWindow::validateCreateGame() {
    ui->create_map_label->setStyleSheet("color: black;");
    ui->create_desc_label->setStyleSheet("color: black;");

    if (ui->map_cbox->currentIndex() == -1) {
        ui->create_map_label->setStyleSheet("color: red;");
        return;
    }

    if (this->ui->desc_txtbox->text().toStdString().length() > MAX_DESCR_CHARS) {
        ui->create_desc_label->setStyleSheet("color: red;");
        return;
    }

    if (this->ui->desc_txtbox->text().toStdString().length() == 0) {
        ui->create_desc_label->setStyleSheet("color: red;");
        return;
    }

    this->client.action_queue.push(
            std::make_shared<CreateGame>(this->ui->desc_txtbox->text().toStdString(),
                                         ui->map_cbox->currentText().toStdString()));

    ui->createMenu->lower();
    ui->desc_txtbox->clear();
    ui->map_cbox->setCurrentIndex(-1);
    showLobby();
}

void MainWindow::showGameSearch() {
    ui->menuScreens->setCurrentIndex((int)SWIndex::GAME_SEARCH);

    ui->searchMovie->setMovie(movie);
    movie->start();

    refreshGameSearch();
}

void MainWindow::refreshGameSearch() {
    games.clear();
    client.action_queue.push(std::make_shared<ShowGames>());

    uint8_t games_q = LobbyListener::getGameFramesQuantity(client.lobby_state_queue);

    for (size_t i = 0; i < games_q; i++) {
        games.push_back(std::make_unique<GameFrame>(ui->gamesAvailable));
        ui->scrollLayout->addWidget(games[i]->frame);
        games[i]->setHandler(*this);
    }

    LobbyListener::setGameFrames(games, client.lobby_state_queue, games_q);
}

void MainWindow::loadHelp() {
    ui->helpMovie->setScaledContents(true);
    ui->helpMovie->setLineWidth(0);
    ui->helpMovie->setMargin(0);
    ui->helpMovie->setGeometry(0, 0, this->width(), this->height());
    ui->helpMovie->lower();

    connect(ui->goMenu_button_2, &QPushButton::clicked, this, [this]() {
        if (this->preHelpIndex == (int)SWIndex::MENU) {
            this->showMenu();
        } else {
            this->showGameSearch();
        }
    });
}

void MainWindow::showHelp() {
    this->preHelpIndex = ui->menuScreens->currentIndex();
    ui->menuScreens->setCurrentIndex((int)SWIndex::HELP);
    movie->start();
    ui->helpMovie->setMovie(movie);
}

void MainWindow::loadLobby() {
    lobby_widgets.push_back({ui->character1_label, ui->ready1_button, ui->player1id_label});
    lobby_widgets.push_back({ui->character2_label, ui->ready2_button, ui->player2id_label});
    lobby_widgets.push_back({ui->character3_label, ui->ready3_button, ui->player3id_label});
    lobby_widgets.push_back({ui->character4_label, ui->ready4_button, ui->player4id_label});

    connect(ui->setReady_button, &QPushButton::pressed, this,
            [this]() { this->client.action_queue.push(std::make_shared<Ready>()); });

    connect(ui->goMenu_button_3, &QPushButton::clicked, this, [this]() {
        // stop timer
        this->client.lobby_state_queue.push(std::make_shared<GameNotJoinable>());
        this->players.clear();
        client.action_queue.push(std::make_shared<ExitGame>());
        this->showGameSearch();
    });
}

void MainWindow::showLobby() {
    uint8_t p_quantity = LobbyListener::getPlayersInLobbyQuantity(client.lobby_state_queue);

    /*
        La idea es recibir NONE jugadores cuando no se pudo unir al juego, o se desea salir del
       lobby
    */
    if (p_quantity == NONE) {
        return;
    }
    /*
        Utilizo un singleshot timer statico ya que es mejor en cuanto a performance, con un QTimer
       instanciado se usaba entre 3 a 5 veces mas CPU
    */
    QTimer::singleShot(33, this, [this] { this->showLobby(); });

    if (p_quantity == NOT_POPPED_COUNT) {
        return;
    }

    games.clear();
    lobbyHideAll();
    players.clear();

    ui->menuScreens->setCurrentIndex((int)SWIndex::LOBBY);

    LobbyListener::setPlayers(players, client.lobby_state_queue, p_quantity);
    setPlayerFrames();

    for (auto& [id, player]: players) {
        player->show();
    }

    startGame();
}

void MainWindow::lobbyHideAll() {
    QLabel *character, *player_id;
    QPushButton* readyButton;
    for (const auto& widgets: lobby_widgets) {
        std::tie(character, readyButton, player_id) = widgets;
        character->hide();
        player_id->hide();
        readyButton->hide();
    }
}

void MainWindow::startGame() {
    for (auto& [id, player]: players) {
        if (not player->ready_state) {
            return;
        }
    }

    initGame = true;

    // stop timer
    this->client.lobby_state_queue.push(std::make_shared<GameNotJoinable>());
    this->close();
}

void MainWindow::setPlayerFrames() {
    QLabel *character, *player_id;
    QPushButton* readyButton;

    for (size_t i = 0; i < players.size(); i++) {
        auto it = players.begin();
        std::advance(it, i);
        std::tie(character, readyButton, player_id) = lobby_widgets[i];
        it->second->setFrame(character, readyButton, player_id);
    }
}

void MainWindow::closeEvent(QCloseEvent* event) {
    client.action_queue.push(std::make_shared<ExitGame>());
    event->accept();
}


MainWindow::~MainWindow() {
    if (ui)
        delete ui;
    if (movie)
        delete movie;
    if (movie_aux)
        delete movie_aux;
    if (timer)
        delete timer;
}

// ---------------- GAME FRAME ---------------------------

GameFrame::GameFrame(QWidget* parent):
        frame(new QWidget(parent)),
        layout(new QHBoxLayout(frame)),
        description(new QLabel(frame)),
        map(new QLabel(frame)),
        players(new QLabel(frame)),
        joinGame(new QPushButton(frame)),
        game_id(0)

{}

void GameFrame::setFrame(const std::string& descrip, const std::string& map_name,
                         const uint8_t& p_quantity, const uint8_t& game_id) {
    this->game_id = game_id;

    std::string quantity(std::to_string(p_quantity));
    quantity = quantity.append(" / 4");

    QString desc = descrip.data();
    QString name_map = map_name.data();
    QString p_quant = quantity.data();

    frame->setLayout(layout);
    frame->setMinimumHeight(70);
    frame->setMaximumHeight(70);

    layout->addWidget(description, 55, Qt::AlignCenter);
    layout->addWidget(map, 15, Qt::AlignCenter);
    layout->addWidget(players, 10, Qt::AlignCenter);
    layout->addWidget(joinGame, 10, Qt::AlignCenter);
    // cppcheck-suppress danglingTemporaryLifetime
    description->setText(desc);
    // cppcheck-suppress danglingTemporaryLifetime
    map->setText(name_map);
    map->setStyleSheet("font-size: 16px;");
    // cppcheck-suppress danglingTemporaryLifetime
    players->setText(p_quant);
    players->setStyleSheet("font-size: 16px;");

    joinGame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    joinGame->setStyleSheet("border-image: url(./client/resources/images/joinGame.bmp);");
    joinGame->setMinimumSize(130, 70);
}

void GameFrame::setHandler(MainWindow& w) {
    MainWindow::connect(joinGame, &QPushButton::clicked, &w, [&w, this]() {
        w.client.action_queue.push(std::make_unique<JoinGame>(this->game_id));
        w.showLobby();
    });
}

void GameFrame::show() {
    frame->show();
    description->show();
    map->show();
    players->show();
    joinGame->show();

    frame->raise();
    description->raise();
    map->raise();
    players->raise();
    joinGame->raise();
}

GameFrame::~GameFrame() {
    delete joinGame;
    delete players;
    delete map;
    delete description;
    delete layout;
    delete frame;
}

// ---------------------------- PLAYER FRAME ------------------------------

PlayerFrame::PlayerFrame(const uint8_t& player_id, const bool& ready):
        character_label(nullptr),
        ready_button(nullptr),
        player_id(nullptr),
        id(player_id),
        ready_state(ready) {}

void PlayerFrame::hide() {
    character_label->hide();
    ready_button->hide();
    this->ready_button->setStyleSheet("border-image: url(./client/resources/images/notReady.png)");
}

void PlayerFrame::setFrame(QLabel* label, QPushButton* button, QLabel* id_label) {
    this->character_label = label;
    this->ready_button = button;
    this->player_id = id_label;
    this->hide();
    // cppcheck-suppress danglingTemporaryLifetime
    QString lblTxt = std::string("Player ID: " + std::to_string(id)).data();
    // cppcheck-suppress danglingTemporaryLifetime
    id_label->setText(lblTxt);
    this->ready();
}


void PlayerFrame::show() {
    character_label->show();
    ready_button->show();
    player_id->show();
}

void PlayerFrame::ready() {
    this->ready_button->setStyleSheet("border-image: url(./client/resources/images/notReady.png)");
    if (ready_state) {
        this->ready_button->setStyleSheet("border-image: url(./client/resources/images/ready.png)");
    }
}
