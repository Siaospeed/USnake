#include "gamewidget.h"

#include <QKeyEvent>
#include <QMessageBox>
#include <QPainter>


GameWidget::GameWidget(GameController* controller, QWidget* parent)
    : QWidget(parent), controller_(controller)
{
    cell_size_ = 20;

    setFixedSize(400, 400);

    qDebug() << controller_;

    setFocusPolicy(Qt::StrongFocus);  // 强制设置为接收焦点
    setFocus();  // 让这个窗口组件获取焦点

    connect(controller_, &GameController::GameUpdated, this, &GameWidget::update);
    connect(controller_, &GameController::GameOver, this, &GameWidget::GameOver);

    qDebug() << controller_;
}

void GameWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    DrawGrid(painter);
    DrawSnake(painter);
    DrawFood(painter);
}

void GameWidget::keyPressEvent(QKeyEvent* event)
{
    qDebug() << event->key();
    switch (event->key())
    {
        case Qt::Key_Left:  controller_->ChangeDirection(Qt::Key_Left);  break;
        case Qt::Key_Right: controller_->ChangeDirection(Qt::Key_Right); break;
        case Qt::Key_Up:    controller_->ChangeDirection(Qt::Key_Up);    break;
        case Qt::Key_Down:  controller_->ChangeDirection(Qt::Key_Down);  break;
        case Qt::Key_P:     break; // TODO: Pause the game
        case Qt::Key_R:     break; // TODO: Reset the game
        default:            QWidget::keyPressEvent(event); break;
    }
}

void GameWidget::resizeEvent(QResizeEvent* event)
{

}

void GameWidget::update()
{
    QWidget::update();
}

void GameWidget::GameOver()
{
    QMessageBox::information(this, tr("Game Over"), tr("You lost!"));
}

void GameWidget::DrawSnake(QPainter& painter)
{
    painter.setBrush(Qt::green);
    const auto& snake = controller_->GetSnake();

    if (snake.empty()) return;

    for (const auto& body : snake)
    {
        painter.drawRect(body.x() * cell_size_, body.y() * cell_size_, cell_size_, cell_size_);
    }

    painter.setBrush(Qt::cyan);
    const auto& head = snake.front();

    painter.drawRect(head.x() * cell_size_, head.y() * cell_size_, cell_size_, cell_size_);
}

void GameWidget::DrawFood(QPainter& painter)
{
    painter.setBrush(Qt::red);
    const auto& food = controller_->GetFood();

    painter.drawRect(food.x() * cell_size_, food.y() * cell_size_, cell_size_, cell_size_);
}

void GameWidget::DrawGrid(QPainter& painter)
{
    int width = controller_->GetWidth();
    int height = controller_->GetHeight();

    painter.setPen(QPen(Qt::lightGray, 1, Qt::DotLine));
    // painter.setPen(QPen(Qt::black, 1));

    for (int x = 0; x <= width * cell_size_; x += cell_size_)
    {
        painter.drawLine(x, 0, x, height * cell_size_);
    }

    for (int y = 0; y <= height * cell_size_; y += cell_size_)
    {
        painter.drawLine(0, y, width * cell_size_, y);
    }
}
