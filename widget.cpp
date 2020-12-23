#include "widget.h"
#include <QWebEngineView>
#include "webenginepage.h"

Widget::Widget(QString yUrl, QWidget *parent)
    : QWidget(parent)
    , m_webEngineView(new QWebEngineView)
    , m_yUrl(yUrl)
    , main(new QHBoxLayout)
{
    setLayout(main);
    m_webEngineView->setObjectName(QStringLiteral("webEngineView"));
    m_webEngineView->setEnabled(true);
    m_webEngineView->setAutoFillBackground(false);
    m_webEngineView->setZoomFactor(1);
    WebEnginePage *page = new WebEnginePage;
    m_webEngineView->setPage(page);
    m_webEngineView->setUrl(QUrl(nullptr));
    if (!m_yUrl.isEmpty())
    {
        m_webEngineView->setUrl(QUrl(m_yUrl));
    }
    connect(m_webEngineView, &QWebEngineView::loadStarted, this, &Widget::on_loadStarted);
    connect(m_webEngineView, &QWebEngineView::loadFinished, this, &Widget::on_loadFinished);
}
Widget::~Widget()
{
}
QWebEnginePage *Widget::getPage()
{
    return this->m_webEngineView->page();
}
void Widget::clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr)
    {
        delete item;
    }
}
void Widget::on_loadStarted()
{
    clearLayout(main);
    main->addStretch();
    main->addStretch();
}
void Widget::on_loadFinished()
{
    clearLayout(main);
    main->addWidget(m_webEngineView);
}
