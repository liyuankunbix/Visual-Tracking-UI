#include "mainwindow.h"
#include <QApplication>
#include <QtitanNavigation.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 加载QSS样式
    QFile qss(":/style.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    MainWindow w;
    w.imagesCount = 0;
    w.show();

//    NavigationMainWindow win2;
//    win2.show();

    return a.exec();
}
