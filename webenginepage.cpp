#include "webenginepage.h"
#include "widget.h"
#include <QFileInfo>
#include <QDesktopServices>

WebEnginePage::~WebEnginePage()
{
}
WebEnginePage::WebEnginePage()
{
    isNewWindow=false;
}
WebEnginePage *WebEnginePage::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type)
    w=new WebEnginePage;
    connect(w,&WebEnginePage::urlChanged,[=](QUrl url)
    {
        onUrlChanged(url,type);
    });
    return w;
}
void WebEnginePage::onUrlChanged(const QUrl url, int type)
{
    isNewWindow=true;
    newWindowType=type;
    QString u = QUrl(url).fileName();
    if(u!=0)
    {
        QDesktopServices::openUrl(url);
    }
     connect(w, nullptr, nullptr, nullptr);
     emit urlChanged(url);
}
