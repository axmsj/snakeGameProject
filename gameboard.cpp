#include "gameboard.h"
#include <QPainter>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QMessageBox>

GameBoard::GameBoard(QWidget *parent)
    : QWidget(parent),
    dir(Right),
    gameOver(false)
{
    setFixedSize(GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE);
    setFocusPolicy(Qt::StrongFocus);

    connect(&timer, &QTimer::timeout, this, &GameBoard::updateGame);
    timer.start(150);   // speed: lower = faster

    resetGame();
}

void GameBoard::resetGame()
{
    snake.clear();
    // start with 3 segments in the middle
    int startX = GRID_WIDTH / 2;
    int startY = GRID_HEIGHT / 2;

    snake.append(QPoint(startX,     startY));
    snake.append(QPoint(startX - 1, startY));
    snake.append(QPoint(startX - 2, startY));

    dir = Right;
    gameOver = false;
    spawnFood();
    update();
}

void GameBoard::spawnFood()
{
    while (true) {
        int x = QRandomGenerator::global()->bounded(GRID_WIDTH);
        int y = QRandomGenerator::global()->bounded(GRID_HEIGHT);
        QPoint candidate(x, y);

        bool onSnake = false;
        for (const auto &p : snake) {
            if (p == candidate) {
                onSnake = true;
                break;
            }
        }

        if (!onSnake) {
            food = candidate;
            break;
        }
    }
}

bool GameBoard::checkCollision(const QPoint &nextHead) const
{
    // wall collision
    if (nextHead.x() < 0 || nextHead.x() >= GRID_WIDTH ||
        nextHead.y() < 0 || nextHead.y() >= GRID_HEIGHT) {
        return true;
    }

    // self collision
    for (const auto &p : snake) {
        if (p == nextHead) {
            return true;
        }
    }
    return false;
}

void GameBoard::moveSnake()
{
    if (gameOver) return;

    QPoint head = snake.first();
    QPoint nextHead = head;

    switch (dir) {
    case Up:    nextHead.ry() -= 1; break;
    case Down:  nextHead.ry() += 1; break;
    case Left:  nextHead.rx() -= 1; break;
    case Right: nextHead.rx() += 1; break;
    }

    if (checkCollision(nextHead)) {
        gameOver = true;
        timer.stop();
        QMessageBox::information(this, "Game Over", "You crashed!");
        // restart automatically for now
        resetGame();
        timer.start(150);
        return;
    }

    // move: add new head
    snake.prepend(nextHead);

    // check food
    if (nextHead == food) {
        spawnFood(); // grow by not removing tail
    } else {
        snake.removeLast(); // normal move: remove tail
    }
}

void GameBoard::updateGame()
{
    moveSnake();
    update();   // triggers paintEvent
}

void GameBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // background
    painter.fillRect(rect(), Qt::black);

    // draw grid (optional, simple)
    painter.setPen(QColor(40, 40, 40));
    for (int x = 0; x <= GRID_WIDTH; ++x)
        painter.drawLine(x * CELL_SIZE, 0, x * CELL_SIZE, height());
    for (int y = 0; y <= GRID_HEIGHT; ++y)
        painter.drawLine(0, y * CELL_SIZE, width(), y * CELL_SIZE);

    // draw food
    painter.setBrush(Qt::red);
    painter.setPen(Qt::NoPen);
    QRect foodRect(food.x() * CELL_SIZE,
                   food.y() * CELL_SIZE,
                   CELL_SIZE, CELL_SIZE);
    painter.drawRect(foodRect);

    // draw snake
    painter.setBrush(Qt::green);
    for (int i = 0; i < snake.size(); ++i) {
        const QPoint &p = snake[i];
        QRect r(p.x() * CELL_SIZE,
                p.y() * CELL_SIZE,
                CELL_SIZE, CELL_SIZE);
        painter.drawRect(r);
    }
}

void GameBoard::keyPressEvent(QKeyEvent *event)
{
    if (gameOver) {
        QWidget::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Up:
        if (dir != Down) dir = Up;
        break;
    case Qt::Key_Down:
        if (dir != Up) dir = Down;
        break;
    case Qt::Key_Left:
        if (dir != Right) dir = Left;
        break;
    case Qt::Key_Right:
        if (dir != Left) dir = Right;
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}
