#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class GameBoard;
class StartMenu;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showGame();
    void closeApp();

private:
    Ui::MainWindow *ui;
    StartMenu *menu;
    GameBoard *board;
};

#endif // MAINWINDOW_H
