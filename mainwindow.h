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
    MainWindow(QString yUrl,
               int nWidth,
               int nHeight,
               QWidget *parent = nullptr);
    ~MainWindow();
    void setIcon(QString yIconPath);
private:
    Widget *m_widget;
    QWidget *downloadProgressBar;
    QAction *m_reloadAction;
    QMessageBox *message;
    bool isCanceled;
    int m_width, m_height;
    QMenu *mainMenu;
private:
    QMenu *createViewMenu();
    QMenu *createHelpMenu();
    QString saveAs(QString fileName);
private slots:
    void on_downloadStart(QWebEngineDownloadItem *item);
    void on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void on_downloadFinish(QString filePath);
    void on_downloadPause(QWebEngineDownloadItem *item);
    void on_downloadResume(QWebEngineDownloadItem *item);
    void on_downloadCancel(QWebEngineDownloadItem *item);
    void about();
signals:
    void sigQuit();
};
#endif // MAINWINDOW_H
