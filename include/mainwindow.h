#ifndef USNAKE_MAINWINDOW_H
#define USNAKE_MAINWINDOW_H

#include "gamewidget.h"
#include "gamecontroller.h"

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void StartGame();
    void PauseGame();

private:
    GameController* game_controller_;
    GameWidget* game_widget_;
    QPushButton* start_button_;
    QPushButton* pause_button_;

private:
    Ui::MainWindow* ui;
};

#endif // !USNAKE_MAINWINDOW_H
