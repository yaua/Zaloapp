#include "mainwindow.h"
#include <QMainWindow>
#include <QToolBar>
#include <QMessageBox>
#include <QFileInfo>
#include <QFileDialog>
#include <QDialog>
#include <QDir>
#include <QCloseEvent>
#include <QDebug>
#include <QMenuBar>
#include "webenginepage.h"

MainWindow::MainWindow(QString yUrl,
                       int nWidth,
                       int nHeight,
                       QWidget *parent)
    : QMainWindow(parent)
    , m_widget(new Widget(yUrl))
    , downloadProgressBar(new QWidget)
    , m_reloadAction (nullptr)
    , message (new QMessageBox())
    , isCanceled(false)
    , m_width(nWidth)
    , m_height(nHeight)
{
    menuBar()->addMenu(createPrintshot());
    menuBar()->addMenu(createHelpMenu());
    resize(m_width, m_height);
    setCentralWidget(m_widget);
    centralWidget()->layout()->setContentsMargins(0, 0, 0, 0);
    connect(m_widget->getPage()->profile(), &QWebEngineProfile::downloadRequested, this, &MainWindow::on_downloadStart);
}

MainWindow::~MainWindow()
{
    emit sigQuit();
    delete m_widget;
}
void MainWindow::about()
{
   QMessageBox::about(this, tr("About Zalo chat webview"),
                            tr("This is a simple chat <b>Application</b> base on Webengineview.\n"
                                "Customize by yaua."
                                "\nIf app has bug, please email: phungngoctho@gmail.com"));
}
QMenu *MainWindow::createPrintshot()
{
    QMenu *printshot = new QMenu("&PrintShot");
    //printshot->exec();
    //if(printshot)

    return printshot;
}
QMenu *MainWindow::createHelpMenu()
{
    QMenu *helpMenu = new QMenu ("&Help");
    helpMenu->addAction(tr("About"),this, &MainWindow::about);
    return helpMenu;
}

QString MainWindow::saveAs(QString fileName)
{
    QString saveFile = QFileDialog::getSaveFileName(this, tr("Save As"), QDir::homePath() + "/Downloads/" + fileName);
    if(!saveFile.isEmpty())
    {
        if(QFileInfo(QFileInfo(saveFile).absolutePath()).permissions().testFlag(QFile::WriteUser))  // Determine whether the upper directory is writable
        {
            return saveFile;
        }
        else
        {
            return saveAs(fileName);
        }
    }
    return nullptr;
}

void MainWindow::on_downloadStart(QWebEngineDownloadItem *item)
{
        QString fileName = QFileInfo(item->downloadFileName()).fileName();
        QString filePath = saveAs(fileName);
        if(filePath.isEmpty())
        {
            return;
        }
        item->setDownloadFileName(filePath);
        filePath = QFileInfo(item->downloadFileName()).absoluteFilePath();
        connect(item, &QWebEngineDownloadItem::downloadProgress, this, &MainWindow::on_downloadProgress);
        connect(item, &QWebEngineDownloadItem::finished, this, [=]()
        {
            on_downloadFinish(filePath);
        });
        item->accept();
        /* DownloadProgressBar*/
        isCanceled = false;
}

void MainWindow::on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    int value = int(double(bytesReceived) / double(bytesTotal) * 100.0);
    message->setWindowTitle("DOWNLOADING");
    message->setText("Start dowwnloading: " + QString::number(value) + "%");
    //this->message->show(); //show messager
}

void MainWindow::on_downloadFinish(QString filePath)
{
    if(!isCanceled)
    {
        QMessageBox message;
        QPushButton *opentButton = message.addButton(tr("Open"), QMessageBox::ActionRole);
        QPushButton *abortButton = message.addButton(QMessageBox::Abort);
        message.setWindowTitle("OPEN FILE FOLDER");
        message.setText(QString("%1 %2 %3").arg(QFileInfo(filePath).fileName()).arg(tr("download finished.")).arg(tr("Show in file manager?")));
        message.exec();
        if(message.clickedButton()==opentButton)
            {
              QProcess proc;
              QString output;
              proc.start("xdg-mime", QStringList() << "query" << "default" << "inode/directory");
              proc.waitForFinished();
              output = proc.readLine().simplified();
              if (output == "dolphin.desktop" || output == "org.kde.dolphin.desktop")
                  proc.startDetached("dolphin", QStringList() << "--select" << filePath);
              else if (output == "nautilus.desktop" || output == "org.gnome.Nautilus.desktop"
                       || output == "nautilus-folder-handler.desktop")
                  proc.startDetached("nautilus", QStringList() << "--no-desktop" << filePath);
              else if (output == "caja-folder-handler.desktop")
                  proc.startDetached("caja", QStringList() << "--no-desktop" << filePath);
              else if (output == "nemo.desktop")
                  proc.startDetached("nemo", QStringList() << "--no-desktop" << filePath);
              else if (output == "kfmclient_dir.desktop")
                  proc.startDetached("konqueror", QStringList() << "--select" << filePath);
              else if (output == "org.thunar.desktop")
                  proc.startDetached("thunar", QStringList() << "--select" << filePath);
             // else
                 // openPath(filePath.left(filePath.lastIndexOf("/")));
                //process->start(exec + filePath);
               // process->start("dolphin --show-item " + filePath);
                //message->hide();'
              message.hide();
            }
            else if (message.clickedButton() == abortButton) { message.hide();
        // abort
             }
    }
}
void MainWindow::on_downloadPause(QWebEngineDownloadItem *item)
{
    item->pause();
}

void MainWindow::on_downloadResume(QWebEngineDownloadItem *item)
{
    item->resume();
}

void MainWindow::on_downloadCancel(QWebEngineDownloadItem *item)
{
    isCanceled = true;  // Cancel download
    item->cancel();
}

