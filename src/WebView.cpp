#include "WebView.h"

int WebView::m_object = 0; //static property

///----------------------------------------------------------------------

WebView::WebView(QWidget *parent): QWidget(parent),
    m_layout(nullptr),
    m_view(nullptr)
{
    WebView::m_object++; //increment the static property
    m_objectId = WebView::m_object;

    m_layout = new QVBoxLayout(this);
    m_view = new QWebEngineView(this);

    QString assetsPath = QCoreApplication::applicationDirPath() + "/assets/web/index2.html";
    m_view->setUrl(QUrl::fromLocalFile(assetsPath));
    m_view->show();
    std::cout << "Url set" << std::endl;

    m_layout->addWidget(m_view);
}

///----------------------------------------------------------------------

WebView::~WebView()
{
    WebView::m_object--; //decrement the static property when destroying the object

    std::cout << "WebView number " << m_objectId << " destroyed" << "\n";
}

///----------------------------------------------------------------------

QWebEngineView *WebView::get_m_view()
{
    return m_view; //return a pointer to m_view
}

///----------------------------------------------------------------------

int WebView::get_m_objectId()
{
    return m_objectId;
}






