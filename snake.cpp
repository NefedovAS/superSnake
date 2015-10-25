#include "snake.h"
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
snake::snake(QWidget *w,QTimer* timer)
{
    snakeTimer=timer;
    diametr=40;
    qsrand(0);
    apple.x=(qrand()%(800/diametr-2)+1) * diametr+diametr/2;
    apple.y=(qrand()%(600/diametr-2)+1) * diametr+diametr/2;;
    parent=w;
    death=false;
    y_shift=diametr;
    x_shift=0;
    createSnake();
}

void snake::createSnake(){
    count = 0;
    for (int i = 0; i< 3; i++)
    {
        cell *newCell=new cell;
        newCell->diametr=diametr;
        newCell->x=200+diametr/2;
        newCell->y=400+diametr/2+diametr*i;
        body_snake.append(newCell);
        count++;
    }
    qDebug()<<death;
}


void snake::animate(QPainter *painter, QPaintEvent *event){
    if(!death){
        for (int i = count-1; i>=0; --i)
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
        for (int i = 1; i<count; i++)
        {
            if(body_snake.at(i)->x==body_snake.at(0)->x && body_snake.at(i)->y==body_snake.at(0)->y)
                death=true;
        }
        if(((body_snake.at(0)->x+diametr/4)>=parent->width() || (body_snake.at(0)->x-diametr/4)<=0)
            || ((body_snake.at(0)->y+diametr/4)>=parent->height()|| (body_snake.at(0)->y-diametr/4)<=0) ){
                death=true;
        }
        if(body_snake.at(0)->x==apple.x && body_snake.at(0)->y==apple.y){
            cell *newCell=new cell;
            newCell->diametr=diametr;
            if(x_shift==0){
                if(y_shift>0){
                    newCell->x=body_snake.at(count-1)->x;
                    newCell->y=body_snake.at(count-1)->y+y_shift;
                }
                else{
                    newCell->x=body_snake.at(count-1)->x;
                    newCell->y=body_snake.at(count-1)->y-y_shift;
                }
            }
            if(y_shift==0){
                if(x_shift>0){
                    newCell->x=body_snake.at(count-1)->x+x_shift;
                    newCell->y=body_snake.at(count-1)->y;
                }
                else{
                    newCell->x=body_snake.at(count-1)->x-x_shift;
                    newCell->y=body_snake.at(count-1)->y;
                }
            }
            body_snake.append(newCell);
            count++;
            apple.x=(qrand()%(800/diametr-2)+1) * diametr+diametr/2;
            apple.y=(qrand()%(600/diametr-2)+1) * diametr+diametr/2;;
        }
            this->draw(painter);
    }
}

void snake::draw(QPainter *painter){
    painter->save();
    for (int i = 0; i< count; i++)
    {
        if(i!=0){
            painter->setPen(QPen(Qt::yellow,3,Qt::SolidLine));
            painter->drawEllipse(body_snake.at(i)->x - diametr/2, body_snake.at(i)->y - diametr/2,diametr, diametr);
        }
        else{
            painter->setPen(QPen(Qt::red,3,Qt::SolidLine));
            painter->drawEllipse(body_snake.at(i)->x - diametr/2, body_snake.at(i)->y - diametr/2,diametr, diametr);
        }

    }
    painter->setPen(QPen(Qt::blue,3,Qt::SolidLine));
    painter->drawEllipse(apple.x - diametr/2, apple.y - diametr/2,diametr, diametr);
    painter->restore();
    if(death){
        snakeTimer->stop();
        QMessageBox msgBox;
        msgBox.setText("Игра закончена");
        msgBox.setInformativeText("Хотите попробывать еще раз?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.setModal(true);
        int ret = msgBox.exec();
        switch (ret) {
          case QMessageBox::Ok:
              body_snake.clear();
              createSnake();
              death=false;
              snakeTimer->start(200);
              x_shift=0;
              y_shift=diametr;
              break;
          case QMessageBox::No:
                QApplication::exit();
              break;
        }
    }
}
