#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QPainter>
#include "snake.h"
class window : public QWidget
{
    Q_OBJECT

public:
    window(QWidget *parent = 0);
    ~window();
protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);

private:
    QPainter painter;
    snake *Snake;
};

#endif // WINDOW_H
