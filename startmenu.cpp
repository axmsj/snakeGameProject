#include "startmenu.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

StartMenu::StartMenu(QWidget *parent)
    : QWidget(parent)
{
    // black background color
    this->setStyleSheet("background-color: black;");

    // Title
    title = new QLabel("Snake Game");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 40px; font-weight: bold; color: #00ff00; background-color: black;");

    // Buttons
    startButton = new QPushButton("Start Game");
    closeButton = new QPushButton("Close Window");

    // Rounded button style
    QString btnStyle =
        "QPushButton { "
        "color: #00ff00; "
        "background-color: black; "
        "border: 2px solid #00ff00; "
        "padding: 10px; "
        "font-size: 20px; "
        "border-radius: 15px;"
        "} "
        "QPushButton:hover { "
        "background-color: #003300; "
        "}";

    //Close Button Hover
    QString closeStyle = btnStyle +
    "QPushButton#closeBtn:hover {"
     "background-color: red;"
    "color: white;"
    "border: 2px solid red;"
    "}";

    //Start Button Hover
    QString startStyle = btnStyle +
    "QPushButton#startBtn:hover {"
    "background-color:blue;"
    "color: white;"
    "border: 2px solid blue;"
    "}";

    closeButton->setObjectName("closeBtn");
    closeButton->setStyleSheet(closeStyle);

    startButton->setObjectName("startBtn");
    startButton->setStyleSheet(startStyle);


    // Layout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(title);
    layout->addWidget(startButton);
    layout->addWidget(closeButton);
    layout->setAlignment(Qt::AlignCenter);

    connect(startButton, &QPushButton::clicked, this, &StartMenu::startGameRequested);
    connect(closeButton, &QPushButton::clicked, this, &StartMenu::closeRequested);
}
