#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gameboard.h"
#include "startmenu.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , menu(nullptr)
    , board(nullptr)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: black;");


    // Start with the menu
    menu = new StartMenu(this);
    setCentralWidget(menu);

    connect(menu, &StartMenu::startGameRequested,
            this, &MainWindow::showGame);
    connect(menu, &StartMenu::closeRequested,
            this, &MainWindow::closeApp);

    resize(600, 600);
}

void MainWindow::showGame()
{
    if (!board) {
        board = new GameBoard(this);
    }
    setCentralWidget(board);   // swap menu → board
}

void MainWindow::closeApp()
{
    QApplication::quit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
