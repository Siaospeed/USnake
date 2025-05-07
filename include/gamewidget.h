#ifndef USNACK_GAMEWIDGET_H
#define USNACK_GAMEWIDGET_H

#include <QPainter>
#include <QWidget>

#include "gamecontroller.h"

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(GameController* controller, QWidget* parent = nullptr);
    // virtual ~GameWidget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void update();
    void GameOver();

private:
    GameController* controller_;

    void DrawSnake(QPainter& painter);
    void DrawFood(QPainter& painter);
    void DrawGrid(QPainter& painter);

    int cell_size_;
};

#endif // !USNACK_GAMEWIDGET_H
