#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QLayout>
#include "webenginepage.h"
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QString yUrl = nullptr, QWidget *parent = nullptr);
    ~Widget();
    QWebEnginePage *getPage();
private:
    QWebEngineView *m_webEngineView;
    QString m_yUrl;
    QHBoxLayout *main;
    void clearLayout(QLayout *layout);
private slots:
    void on_loadStarted();
    void on_loadFinished();
};
#endif // WIDGET_H
