#include "gamecontroller.h"

#include <ctime>

#include <deque>
#include <random>

#include <QWidget>

GameController::GameController(QWidget* game_area)
    : QObject(game_area),
      timer_(new QTimer(this)),
      timer_interval_(300)
{
    qDebug() << "GameController::GameController()";
    connect(timer_, &QTimer::timeout, this, &GameController::update);
    qDebug() << "GameController::GameController()";
}

void GameController::StartGame()
{
    qDebug() << "Starting game";
    snake_.clear();
    snake_.emplace_back(5, 5);
    snake_.emplace_back(4, 5);
    snake_.emplace_back(3, 5);

    Q_ASSERT(!snake_.empty());

    direction_ = DIRECTION::RIGHT;

    width_ = 20;
    height_ = 20;

    score_ = 30;

    emit ScoreChanged(score_);

    GenerateFood();

    timer_->start(timer_interval_);
}

void GameController::ChangeDirection(Qt::Key key)
{
    DIRECTION new_direction;

    switch (key)
    {
        case Qt::Key_Left:  new_direction = DIRECTION::LEFT;  break;
        case Qt::Key_Right: new_direction = DIRECTION::RIGHT; break;
        case Qt::Key_Up:    new_direction = DIRECTION::UP;    break;
        case Qt::Key_Down:  new_direction = DIRECTION::DOWN;  break;
        default: return;
    }

    if ((direction_ == DIRECTION::LEFT  && new_direction == DIRECTION::RIGHT) ||
        (direction_ == DIRECTION::RIGHT && new_direction == DIRECTION::LEFT)  ||
        (direction_ == DIRECTION::UP    && new_direction == DIRECTION::DOWN)  ||
        (direction_ == DIRECTION::DOWN  && new_direction == DIRECTION::UP))
    {
        return;
    }

    direction_ = new_direction;
}

void GameController::SetTimerInterval(int ms)
{
    this->timer_interval_ = ms;
}

const std::deque<QPoint>& GameController::GetSnake() const
{
    // Q_ASSERT(!snake_.empty());
    return this->snake_;
}

const QPoint& GameController::GetFood() const
{
    return this->food_;
}

int GameController::GetScore() const
{
    return this->score_;
}

int GameController::GetWidth() const
{
    return this->width_;
}

int GameController::GetHeight() const
{
    return this->height_;
}

void GameController::update()
{
    // if (snake_.empty()) return;

    qDebug() << "update triggered";
    Q_ASSERT(!snake_.empty());  // 保留断言

    // direction_ = pending_direction_;

    QPoint head = snake_.front();
    QPoint new_head = head;

    switch (direction_)
    {
        case DIRECTION::UP:    new_head.ry() -= 1; break;
        case DIRECTION::DOWN:  new_head.ry() += 1; break;
        case DIRECTION::LEFT:  new_head.rx() -= 1; break;
        case DIRECTION::RIGHT: new_head.rx() += 1; break;
    }

    auto collision = CheckCollision(new_head);
    if (collision == CollisionType::SELF || collision == CollisionType::WALL)
    {
        timer_->stop();
        emit GameOver();
        return;
    }

    snake_.push_front(new_head);

    if (collision == CollisionType::FOOD)
    {
        score_ += 10;
        emit ScoreChanged(score_);
        GenerateFood();
    }
    else
    {
        snake_.pop_back();
    }

    emit GameUpdated();
}

void GameController::GenerateFood()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dX(0, width_ - 1);
    std::uniform_int_distribution<> dY(0, height_ - 1);

    int gx, gy;

    do
    {
        gx = dX(gen);
        gy = dY(gen);
    }
    while ([&]
    {
        for (auto& [x, y] : snake_)
        {
            if (gx == x && gy == y) return true;
        }
        return false;
    }());

    food_ = {gx, gy};
}

GameController::CollisionType GameController::CheckCollision(const QPoint& head_pos) const
{
    if (head_pos.x() < 0 || head_pos.x() >= width_ ||
        head_pos.y() < 0 || head_pos.y() >= height_)
    {
        return CollisionType::WALL;
    }

    for (int i = 1; i < snake_.size(); ++i)
    {
        if (head_pos == snake_[i])
        {
            return CollisionType::SELF;
        }
    }

    if (head_pos == food_)
    {
        return CollisionType::FOOD;
    }

    return CollisionType::NONE;
}
