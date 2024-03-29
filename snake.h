#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QTimer>
struct cell
{
    int x;
    int y;
    int diametr;
};

struct eda
{
    int x;
    int y;
    int diametr;
};
struct obstacle{    // Препятствие
    int x;
    int y;
};

class snake
{
public:
    snake(QWidget *w, QTimer *timer);
public:
    QTimer *snakeTimer;
    int x,y,count,diametr;
    void createSnake();
    void animate(QPainter *painter, QPaintEvent *event);
    void draw(QPainter *painter);
    QList<cell*> body_snake;
    QList<cell*> new_body_snake;
    int x_shift,y_shift;
    bool death;
    QWidget *parent;
    eda apple;
    void fCourse();
    bool control;                                           // Управление
    bool *course;                                           // Возможность хода
    void create_obstacle();                                 // Расстановка препятствий
    QList<obstacle*> obstacle_list;                         // Список препятствий
};

#endif // SNAKE_H
