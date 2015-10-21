#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QPainter>
#include <QPaintEvent>
struct cell
{
    int x;
    int y;
    int radius;
};

class snake
{
public:
    snake();
public:
    int x,y,count,radius;
    void createSnake();
    void animate(QPainter *painter, QPaintEvent *event);
    void draw(QPainter *painter);
    QList<cell*> body_snake;
    QList<cell*> new_body_snake;
    int x_shift,y_shift;
};

#endif // SNAKE_H
