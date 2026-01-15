#include "WebView.h"

int WebView::m_object = 0; //static property

///----------------------------------------------------------------------

WebView::WebView(QWidget *parent): QWidget(parent),
    m_layout(nullptr),
    m_view(nullptr),
    webSettings(nullptr)
{
    WebView::m_object++; //increment the static property
    m_objectId = WebView::m_object;

    m_layout = new QVBoxLayout(this);
    m_view = new QWebEngineView(this);

    m_view->setUrl(QUrl("file:///home/h1534hheasa/etude/navigateur/Sasaki/bin/assets/web/index2.html"));
    m_view->show();
    std::cout << "Url set" << std::endl;

//    webSettings = m_view->settings();
//    webSettings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);

    m_layout->addWidget(m_view);
}

///----------------------------------------------------------------------

WebView::~WebView()
{
    WebView::m_object--; //decrement the static property when destroying the object

    delete webSettings;
    webSettings = nullptr;

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






