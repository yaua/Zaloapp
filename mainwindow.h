#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QToolButton>
#include <QProgressBar>
#include <QPushButton>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QLayout>
#include <QProcess>
#include "widget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QString yTitle,
               QString yUrl,
               int nWidth,
               int nHeight,
               QWidget *parent = nullptr);
    ~MainWindow();
    void setIcon(QString yIconPath);
private:
    Widget *m_widget;
    QWidget *downloadProgressBar;
    QProgressBar *bar;
    QPushButton *pause;
    QPushButton *resume;
    QPushButton *cancel;
    QHBoxLayout *progress;
    QMessageBox *message;
    QProcess *process;
    bool isCanceled;
    int m_width, m_height;
    QString saveAs(QString fileName);
private slots:
   // void contextMenuEvent(QMenu *menu);
    void on_downloadStart(QWebEngineDownloadItem *item);
    void on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void on_downloadFinish(QString filePath);
    void on_downloadPause(QWebEngineDownloadItem *item);
    void on_downloadResume(QWebEngineDownloadItem *item);
    void on_downloadCancel(QWebEngineDownloadItem *item);
signals:
    void sigQuit();
};
#endif // MAINWINDOW_H
