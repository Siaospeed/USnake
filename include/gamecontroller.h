#ifndef USNAKE_GAMECONTROLLER_H
#define USNAKE_GAMECONTROLLER_H

#include <deque>

#include <QObject>
#include <QPoint>
#include <QTimer>

/**
 * @class GameController
 * @brief Controls the main game logic for the USnake game.
 *
 *  This class handles game state updates, including snack movement,
 *  food generation, collision detection, and scoring. It emits Qt
 *  signals to notify the UI of game events.
 */
class GameController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructs a GameController instance, initializes timer and connects update slots.
     * @param game_area Pointer to the QWidget where the game is rendered.
     */
    explicit GameController(QWidget* game_area);

    /**
     * @brief Starts a new game session.
     *
     * Initializes the snake, score, and food detection.
     * Starts the update timer.
     */
    void StartGame();

    /**
     * @brief Changes the snake's direction.
     * @param key A Qt key representing the new direction.
     *
     * Ignores changes to opposite direction to prevent instant reversal.
     */
    void ChangeDirection(Qt::Key key);

    /**
     * @brief Sets the update interval for the game timer.
     * @param ms Interval in milliseconds.
     */
    void SetTimerInterval(int ms);

    /**
     * @brief Returns a reference to the current snake body.
     * @return A const reference to the deque of QPoint representing the snake.
     */
    [[nodiscard]] const std::deque<QPoint>& GetSnake() const;

    /**
     * @brief Returns the position of the current food.
     * @return A const reference to the QPoint of the food.
     */
    [[nodiscard]] const QPoint& GetFood() const;

    /**
     * @brief Returns the current score.
     * @return The player's score.
     */
    [[nodiscard]] int GetScore() const;

    /**
     * @brief Returns the width of the game grid.
     * @return Width in cells.
     */
    [[nodiscard]] int GetWidth() const;

    /**
     * @brief Return the height of the game grid.
     * @return Height in cells.
     */
    [[nodiscard]] int GetHeight() const;

signals:
    /**
     * @brief Emitted when the game state has been updated.
     */
    void GameUpdated();

    /**
     * @brief Emitted when the score changes.
     * @param new_score The updated score.
     */
    void ScoreChanged(int new_score);

    /**
     * @brief Emitted when the game has been paused.
     */
    void GamePaused();

    /**
     * @brief Emitted when the game has been resumed.
     */
    void GameResumed();

    /**
     * @brief Emitted when the game ends due to collision.
     */
    void GameOver();

public slots:
    /**
     * @brief Called at
     */
    void TogglePause();

private slots:
    /**
     * @brief Called at each timer tick to update the game state.
     */
    void update();

private:
    enum class DIRECTION { UP, DOWN, LEFT, RIGHT };
    enum class CollisionType { NONE, WALL, SELF, FOOD };

    std::deque<QPoint> snake_;
    DIRECTION direction_;

    QPoint food_;
    QTimer* timer_;
    int score_;
    bool is_paused_;

    int width_;
    int height_;

    int timer_interval_;

    void GenerateFood();
    CollisionType CheckCollision(const QPoint& head_pos) const;
};

#endif // !USNAKE_GAMECONTROLLER_H
