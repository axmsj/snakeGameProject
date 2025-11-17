#ifndef STARTMENU_H
#define STARTMENU_H


#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class QPushButton;
class QLabel;

class StartMenu : public QWidget
{
    Q_OBJECT

public:
    explicit StartMenu(QWidget *parent = nullptr);

signals:
    void startGameRequested();
    void closeRequested();

private:
    QLabel *title;
    QPushButton *startButton;
    QPushButton *closeButton;
};

#endif // STARTMENU_H
