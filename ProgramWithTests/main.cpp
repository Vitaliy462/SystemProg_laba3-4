#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << QSqlDatabase::drivers();
    MainWindow w;
    w.show();
    return a.exec();
}
