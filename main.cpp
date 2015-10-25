#include "window.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
        window w;
        w.show();

    return a.exec();
}
