#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QWidget>
#include <QTimer>
#include <QVector>
#include <QPoint>

class GameBoard : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoard(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateGame();   // called by timer

private:
    enum Direction {
        Up,
        Down,
        Left,
        Right
    };

    void resetGame();
    void spawnFood();
    void moveSnake();
    bool checkCollision(const QPoint &nextHead) const;

    QTimer timer;
    QVector<QPoint> snake;   // snake body: [0] is head
    QPoint food;

    Direction dir;
    bool gameOver;

    static const int CELL_SIZE = 25;   // pixels per cell
    static const int GRID_WIDTH  = 25; // 25 * 20 = 500 px
    static const int GRID_HEIGHT = 25;
};

#endif // GAMEBOARD_H
