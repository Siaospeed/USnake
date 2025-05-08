#include "mainwindow.h"
#include "../ui_mainwindow.h"

#include <QBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , game_controller_(new GameController(this))
    , game_widget_(new GameWidget(game_controller_, this))
    , ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow::MainWindow()";
    ui->setupUi(this);

    auto central = new QWidget(this);
    auto layout = new QVBoxLayout(central);
    layout->setContentsMargins(50, 50, 0, 0); // 左50、上50，右下为0
    layout->addWidget(game_widget_);
    setCentralWidget(central);

    start_button_ = new QPushButton("Start Game", this);
    start_button_->setGeometry(500, 450, 100, 30);  // 设置按钮位置和大小
    connect(start_button_, &QPushButton::clicked, this, &MainWindow::StartGame);

    pause_button_ = new QPushButton("Pause", this);
    pause_button_->setGeometry(650, 450, 100, 30);
    connect(pause_button_, &QPushButton::clicked, this, &MainWindow::PauseGame);

    score_display_ = new QLCDNumber(this);
    score_display_->setDigitCount(4);
    score_display_->setSegmentStyle(QLCDNumber::Flat);
    score_display_->setGeometry(575, 250, 100, 30);
    connect(game_controller_, &GameController::ScoreChanged, this, &MainWindow::UpdateScore);

    qDebug() << "MainWindow::MainWindow()";
}

void MainWindow::StartGame()
{
    game_controller_->StartGame();
    game_widget_->setFocus();
}

void MainWindow::PauseGame()
{
    // 暂停或恢复游戏
}

void MainWindow::UpdateScore(int new_score)
{
    score_display_->display(new_score);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionEasy_triggered()
{
    game_controller_->SetTimerInterval(500);
}


void MainWindow::on_actionNormal_triggered()
{
    game_controller_->SetTimerInterval(300);
}

void MainWindow::on_actionHard_triggered()
{
    game_controller_->SetTimerInterval(100);
}
