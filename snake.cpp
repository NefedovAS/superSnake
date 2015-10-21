#include "snake.h"
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
snake::snake()
{
    y_shift=radius;
    x_shift=0;
    radius=20;
    createSnake();
}

void snake::createSnake(){
    count = 0;
    for (int i = 0; i< 7; i++)
    {
        cell *newCell=new cell;
        newCell->radius=radius;
        newCell->x=200;
        newCell->y=200+radius*i;
        body_snake.append(newCell);
        count++;
    }
}


void snake::animate(QPainter *painter, QPaintEvent *event){
    for (int i = 6; i>=0; --i)
    {
        if(i==0){
            body_snake.at(i)->x = body_snake.at(i)->x - x_shift;
            body_snake.at(i)->y = body_snake.at(i)->y - y_shift;
        }
        else{
            body_snake.at(i)->x = body_snake.at(i-1)->x;
            body_snake.at(i)->y = body_snake.at(i-1)->y;
        }
    }

    this->draw(painter);
}

void snake::draw(QPainter *painter){
    painter->save();
    for (int i = 0; i< 7; i++)
    {
            painter->setPen(QPen(Qt::yellow,3,Qt::SolidLine));
        painter->drawEllipse(body_snake.at(i)->x - radius/2, body_snake.at(i)->y - radius/2,radius, radius);
    }

    painter->restore();
}
