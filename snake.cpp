#include "snake.h"
#include <QPainter>
#include <QPaintEvent>
#include <QColor>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <cstdlib>
#include <ctime>
snake::snake(QWidget *w,QTimer* timer)
{
    QMessageBox msgBox;
    msgBox.setText("Управление");
    msgBox.setInformativeText("Включить ручное управление?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setModal(true);
    int ret = msgBox.exec();
    switch (ret) {
      case QMessageBox::Ok:
          control = true;
          break;
      case QMessageBox::No:

          break;
    }
    course = new bool[4];
    snakeTimer=timer;
    //диаметр звена змейки и синего яблока
    diametr=40;
    qsrand(0);
    parent=w;
    //показатель жизни змейки
    death=false;
    //начальные параметры движения
    y_shift=diametr;
    x_shift=0;
    create_obstacle();
    createSnake();
    /*
     Генерируем синие яблоко и проверяем
     возможность его появления на координатах змейки
    */
    bool edaVzmeike=true;
    while(edaVzmeike){
        edaVzmeike=false;
        apple.x=(qrand()%(800/diametr-2)+1) * diametr+diametr/2;
        apple.y=(qrand()%(600/diametr-2)+1) * diametr+diametr/2;
        for (int i = 0; i< count; i++)
        {
            if(apple.x==body_snake.at(i)->x && apple.y==body_snake.at(i)->y){
                edaVzmeike=true;
                break;
            }

        }
    }

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
}

void snake::fCourse()
{
    for(int i = 0; i < 4; i++)
        course[i] = true;
    for(int i = 0; i < body_snake.count(); i++)
    {
        if(body_snake.at(0)->x == body_snake.at(i)->x && body_snake.at(0)->y - body_snake.at(i)->y == diametr)
            course[1] = false;
        if(body_snake.at(0)->x == body_snake.at(i)->x && body_snake.at(0)->y - body_snake.at(i)->y == -diametr)
            course[3] = false;
        if(body_snake.at(0)->y == body_snake.at(i)->y && body_snake.at(0)->x - body_snake.at(i)->x == diametr)
            course[0] = false;
        if(body_snake.at(0)->y == body_snake.at(i)->y && body_snake.at(0)->x - body_snake.at(i)->x == -diametr)
            course[2] = false;
    }

    for(int i = 0; i < obstacle_list.count(); i++)
    {
        if(body_snake.at(0)->x == obstacle_list.at(i)->x && body_snake.at(0)->y - obstacle_list.at(i)->y == diametr)
            course[1] = false;
        if(body_snake.at(0)->x == obstacle_list.at(i)->x && body_snake.at(0)->y - obstacle_list.at(i)->y == -diametr)
            course[3] = false;
        if(body_snake.at(0)->y == obstacle_list.at(i)->y && body_snake.at(0)->x - obstacle_list.at(i)->x == diametr)
            course[0] = false;
        if(body_snake.at(0)->y == obstacle_list.at(i)->y && body_snake.at(0)->x - obstacle_list.at(i)->x == -diametr)
            course[2] = false;

    }

}

void snake::animate(QPainter *painter, QPaintEvent *event){
    if(!death){
        if(!control) // Интеллект. Направление к яблоку.
        {

            y_shift = 0;
            fCourse();
            if(body_snake.at(0)->x < apple.x && course[2])
                x_shift = -diametr;
            if(body_snake.at(0)->x > apple.x && course[0])
                x_shift = diametr;
            if(body_snake.at(0)->x == apple.x)
            {
                x_shift = 0;
                if(body_snake.at(0)->y < apple.y && course[3])
                    y_shift = -diametr;
                else
                    if(body_snake.at(0)->y > apple.y && course[1])
                        y_shift = diametr;
                    else
                        if(course[2])
                            x_shift = -diametr;
                        else
                            if(course[0])
                                x_shift = diametr;
                            else
                                if(course[3])
                                    y_shift = -diametr;
                                else
                                    if(course[1])
                                        y_shift = diametr;

            }


        }
        for (int i = count-1; i>=0; --i)
        {
            //расчёт головы змейки
            if(i==0){
                body_snake.at(i)->x = body_snake.at(i)->x - x_shift;
                body_snake.at(i)->y = body_snake.at(i)->y - y_shift;
            }
            //расчёт остальной части
            else{
                body_snake.at(i)->x = body_snake.at(i-1)->x;
                body_snake.at(i)->y = body_snake.at(i-1)->y;
            }
        }
        //проверка столкновения головы змейки с телом
        for (int i = 1; i<count; i++)
        {
            if(body_snake.at(i)->x==body_snake.at(0)->x && body_snake.at(i)->y==body_snake.at(0)->y)
                death=true;
        }
        // Столкновение с препятствием

        for(int i = 0; i < obstacle_list.count(); i++)
        {
            if(body_snake.at(0)->x==obstacle_list.at(i)->x && body_snake.at(0)->y==obstacle_list.at(i)->y)
            {
                death = true;
                break;
            }
        }


        if(body_snake.at(0)->x+diametr/4>=parent->width())      // Выход за правую границу
        {
            body_snake.at(0)->x = body_snake.at(0)->x - parent->width();
        }
        if(body_snake.at(0)->x-diametr/4<=0)                    // Выход за левую границу
        {
            body_snake.at(0)->x = body_snake.at(0)->x + parent->width();
        }
        if(body_snake.at(0)->y+diametr/4>=parent->height())     // Выход за нижнюю границу
        {
            body_snake.at(0)->y = body_snake.at(0)->y - parent->height();
        }
        if(body_snake.at(0)->y-diametr/4<=0)                    // Выход за верхнюю границу
        {
            body_snake.at(0)->y = body_snake.at(0)->y + parent->height();
        }
        //если змея сьела яблоко, то удлиняем тело
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
            /*
             Вновь генерируем синие яблоко и проверяем
             возможность его появления на координатах змейки
            */
            bool edaVzmeike=true;
            while(edaVzmeike){
                edaVzmeike=false;
                apple.x=(qrand()%(800/diametr-2)+1) * diametr+diametr/2;
                apple.y=(qrand()%(600/diametr-2)+1) * diametr+diametr/2;
                for (int i = 0; i< count; i++)
                {
                    if(apple.x==body_snake.at(i)->x && apple.y==body_snake.at(i)->y){
                        edaVzmeike=true;
                        break;
                    }

                }
            }
        }
            this->draw(painter);
    }
}

void snake::draw(QPainter *painter){
    painter->save();
    //рисуем змейку
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
    for(int i = 0; i < obstacle_list.count(); i++) // Отрисовка препятствий
    {
        painter->setPen(QPen(Qt::gray,3,Qt::SolidLine));
        painter->drawEllipse(obstacle_list.at(i)->x - diametr/2, obstacle_list.at(i)->y - diametr/2,diametr, diametr);
    }
    //рисуем синее яблоко
    painter->setPen(QPen(Qt::blue,3,Qt::SolidLine));
    painter->drawEllipse(apple.x - diametr/2, apple.y - diametr/2,diametr, diametr);
    painter->restore();
    //если смерть, останавливаем таймер перерисовки и выводим сообщение о проигрыше
    if(death){
        snakeTimer->stop();
        QMessageBox msgBox;
        msgBox.setText("Игра закончена");
        msgBox.setInformativeText("Хотите попробовать еще раз?");
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
void snake::create_obstacle()   // Расстановка препятствий
{
    srand(time(NULL));
    obstacle_list.append(new obstacle);
    obstacle_list.at(0)->x = rand() % parent->width();
    obstacle_list.at(0)->x = obstacle_list.at(0)->x - (obstacle_list.at(0)->x % diametr) - diametr / 2;
    obstacle_list.at(0)->y = rand() % parent->height();
    obstacle_list.at(0)->y = obstacle_list.at(0)->y - (obstacle_list.at(0)->y % diametr) - diametr / 2;

    obstacle_list.append(new obstacle);
    obstacle_list.at(1)->x = obstacle_list.at(0)->x + diametr;
    obstacle_list.at(1)->y = obstacle_list.at(0)->y;
    //obstacle_list.at(1)->x += diametr;

    obstacle_list.append(new obstacle);
    obstacle_list.at(2)->x = obstacle_list.at(1)->x;
    obstacle_list.at(2)->y = obstacle_list.at(1)->y + diametr;

    obstacle_list.append(new obstacle);
    //obstacle_list.at(3) = obstacle_list.at(2);
    obstacle_list.at(3)->x = rand() % parent->width();
    obstacle_list.at(3)->x = obstacle_list.at(3)->x - (obstacle_list.at(3)->x % diametr) - diametr / 2;
    obstacle_list.at(3)->y = rand() % parent->height();
    obstacle_list.at(3)->y = obstacle_list.at(3)->y - (obstacle_list.at(3)->y % diametr) - diametr / 2;

    obstacle_list.append(new obstacle);
    obstacle_list.at(4)->x = obstacle_list.at(3)->x + diametr;
    obstacle_list.at(4)->y = obstacle_list.at(3)->y;

    obstacle_list.append(new obstacle);
    obstacle_list.at(5)->x = obstacle_list.at(4)->x;
    obstacle_list.at(5)->y = obstacle_list.at(4)->y + diametr;

    obstacle_list.append(new obstacle);
    obstacle_list.at(6)->x = obstacle_list.at(5)->x + diametr;
    obstacle_list.at(6)->y = obstacle_list.at(5)->y;

    qDebug("%d", obstacle_list.count());


}


