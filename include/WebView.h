#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <iostream>

#include <QWidget>
#include <QWebEngineView>
#include <QVBoxLayout>
#include <QWebEngineSettings>

class WebView: public QWidget
{

public:
    WebView(QWidget *parent = nullptr);
    ~WebView();

    //accessor(s)
    QWebEngineView *get_m_view();
    int get_m_objectId();

protected:
    static int m_object; // Used to count the WebView object instancied
    int m_objectId;
    QVBoxLayout *m_layout;
    QWebEngineView *m_view;
    QWebEngineSettings *webSettings;

};

#endif // WEBVIEW_H
