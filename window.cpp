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

