#include "MainWidget.h"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/image/logo.ico"));
    MainWidget w;
    w.show();
    return a.exec();
}
