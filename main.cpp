#include "mainwindow.h"
#include <QApplication>
#include <QMainWindow>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setWindowIcon(QIcon(":/images/zalo.svg"));
    QString yDefaultDesc = QString("<span style=' font-size:8pt; font-weight:600;'>This is the simple app with dtk lib and WebApp Runtime. Customize by yaua</span>");
    QString yTitle = "Zalo";
    QString yUrl = "https://chat.zalo.me/";
    int width = 700;
    int height = 800;
    bool tray = true;
    a.setQuitOnLastWindowClosed(!tray);
    MainWindow w(yTitle, yUrl, width, height, tray);
    w.show();
    return a.exec();
}
