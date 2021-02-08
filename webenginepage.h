#ifndef WEBENGINEPAGE_H
#define WEBENGINEPAGE_H
#include <QWebEnginePage>
#include <QObject>
#include <QWebEngineProfile>

class WebEnginePage : public QWebEnginePage
{
public:
    WebEnginePage();
    ~WebEnginePage();
    bool isNewWindow;
    WebEnginePage *w;
    QWebEngineProfile profile;
    int newWindowType;
private:
    WebEnginePage *createWindow(QWebEnginePage::WebWindowType type);
signals:
    void newWindow(QUrl);
public slots:
    void onUrlChanged(QUrl, int type);
};
#endif // WEBENGINEPAGE_H
