#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setWindowIcon(QIcon(":/images/zalo.svg"));
    QString yUrl = "https://chat.zalo.me/";
    int width = 700;
    int height = 800;
    MainWindow w(yUrl, width, height);
    w.show();
    w.setWindowTitle("Zalo web chat");
    return a.exec();
}
