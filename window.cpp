#include "window.h"
#include <QTimer>
#include <QDebug>

window::window(QWidget *parent)
    : QWidget(parent)
{
    Snake=new snake;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(100);
    setStyleSheet("background-color:green;");
}

window::~window()
{

}

void window::paintEvent(QPaintEvent *event)
{
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    Snake->animate(&painter, event);
    painter.end();
}

void window::keyPressEvent(QKeyEvent *event)
{
  switch (event->key()) {
    case 16777235:
        if(Snake->y_shift>=0){
            Snake->x_shift=0;
            Snake->y_shift=Snake->radius;
        }
        break;
    case 16777237:
      if(Snake->y_shift<=0){
          Snake->x_shift=0;
          Snake->y_shift=-Snake->radius;
      }
        break;
    case 16777234:
      if(Snake->x_shift>=0){
          Snake->x_shift=Snake->radius;
          Snake->y_shift=0;
      }
          break;
    case 16777236:
      if(Snake->x_shift<=0){
          Snake->x_shift=-Snake->radius;
          Snake->y_shift=0;
      }
        break;
  }
}
