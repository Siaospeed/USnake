#ifndef USNAKE_GAMECONTROLLER_H
#define USNAKE_GAMECONTROLLER_H

#include <deque>

#include <QObject>
#include <QPoint>
#include <QTimer>

class GameController : public QObject
{
    Q_OBJECT

public:
    explicit GameController(QWidget* game_area);

    void StartGame();
    void ChangeDirection(Qt::Key key);
    [[nodiscard]] const std::deque<QPoint>& GetSnake() const;
    [[nodiscard]] const QPoint& GetFood() const;
    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetHeight() const;

signals:
    void GameUpdated();
    void GameOver();

private slots:
    void update();

private:
    enum class DIRECTION { UP, DOWN, LEFT, RIGHT };
    enum class CollisionType { NONE, WALL, SELF, FOOD };

    std::deque<QPoint> snake_;
    DIRECTION direction_;
    QPoint food_;
    QTimer* timer_;
    int score_;

    int width_;
    int height_;

    void GenerateFood();
    CollisionType CheckCollision(const QPoint& head_pos) const;
};

#endif // !USNAKE_GAMECONTROLLER_H
