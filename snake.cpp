#include "snake.h"
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
snake::snake()
{
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
