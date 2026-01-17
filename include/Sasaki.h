#ifndef SASAKI_H
#define SASAKI_H

/// = = = = = Local
#include "WebView.h"
#include "StatusBar.h"
#include "History.h"
//#include "Star.h"
#include "Settings.h"

/// = = = = = C++
#include <iostream>

/// = = = = = Qt
#include <QObject>

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QKeySequence>
#include <QIcon>
#include <QToolBar>
#include <QLineEdit>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QWebEngineView>
#include <QUrl>
#include <QWebEngineHistory>
#include <QFile>
#include <QTextStream>
#include <QStringLiteral>
#include <QWebEngineView>
#include <QFont>

class Sasaki: public QMainWindow
{
Q_OBJECT

public:
    Sasaki(QWidget *parent = nullptr);
    ~Sasaki();

    //accessor(s)
    QWebEngineView *get_currentWebView();
    int get_currentIndex();
    int get_currentWebViewIndex();
    QWebEngineHistory *get_currentWebViewHistory();

    //signal emitter
    void SemitSignal();

    void SaddMenu();
    void ScreateNavigationSubMenu();
    void SaddActionToNavigationSubMenu();
    void ScreateAction();
    void SconfigureAction();
    void SaddActionToMenu();
    void SconnectAction();
    void SaddToolBar();
    void SaddActionToToolBar();
    void ScreateWidget();
    void SconfigureWidget();

    /// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

    void ScreateCentralWidget();
    void SconfigureCentralWidget();
    void SsetCentralWidget();
    void ScreateSubWindow();
    void SconfigureSubWindow();
    void SaddWidgetToCentralLayout();
    void SconnectWidget();
    void SconnectDependentWidgAct(); // used to connect dependent SIGNAL( QWidget, QAction or another ) on page

    /// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

    void ScreateStatusBar();
    void SconfigureStatusBar();

    /// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

    void SReadWriteHistory();
    bool isPreferred();
    void loadSettings(QWebEngineView *page = nullptr);

    /// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
    /// STATIC METHODS

    static QString SfirstString(QString string);
    static QString SfirstString(QString string, QString separator);
    static QString SlastString(QString string);
    static QString SlastString(QString string, QString separator);


protected:
    /// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

    ///---------- menus
    QMenu *m_navigationMenu;
    QMenu *m_settingMenu;
    QMenu *m_aboutMenu;

    ///---------- submenus
    QMenu *m_recentLinkSubMenu;

    ///---------- actions
    QAction *m_actionFind;
    QAction *m_actionCloseTab;
    QAction *m_actionCloseAllTab;
    QAction *m_actionPreviousPage;
    QAction *m_actionNextPage;
    QAction *m_actionReloadPage;
    QAction *m_actionHome;
    QAction *m_actionCancel;
    QAction *m_actionLaunch;
    QAction *m_actionPreferedPage;
    QAction *m_actionQuit;
    QAction *m_actionHistory;
    QAction *m_actionClearHistory;
    QAction *m_actionFavorite;

    ///---------- tool bar
    QToolBar *m_toolBar;

    ///---------- widgets
    QLineEdit *m_urlEdit;
    QLineEdit *m_searchEdit;

    /// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

    QMdiArea *m_centralZone;
    QWidget *m_centralWidget;
    QMdiSubWindow *m_subWindow1;
    QVBoxLayout *m_layout;
    QPushButton *m_buttonNewTab;
    QTabWidget *m_tabView;
    std::vector<WebView *> page;

    ///---------- status bar
    StatusBar *m_statusBar;

    ///---------- history
    QWebEngineHistory *history;

    std::vector<QAction *> title;


public slots:
    int sl_addNewTab(); // used for adding new tab to m_tabView (QTabWidget), return 0 if a tab was added, -1 otherwise
    int sl_removeTab(const int index); // used for removing a tab, return 0 if a tab was removed, -1 otherwise
    int sl_removeTab();
    int sl_tabChanged(const int index);
    int sl_removeAllTabs(); // used for removing all tabs
    int sl_urlChanged(const QUrl url);
    int sl_runUrl();
    int sl_titleChanged(const QString title);
    int sl_back();
    int sl_next();
    int sl_reload();
    int sl_loadStarted();
    int sl_loadFinished(const bool ok);
    int sl_progress(int progress);
    int sl_cancelLoading();
    int sl_canGoBack();
    int sl_noBack();
    int sl_canGoNext();
    int sl_noNext();
    int sl_returnHome();
    int sl_iconChanged(const QIcon icon);
    int sl_runUrl(QString url);
    int sl_openHistory();
    int sl_clearHistory();
    int sl_addPageToFavorite(bool ok);
    int sl_removePageFromFavorite(bool ok);
    bool sl_favoritePage();
    bool sl_notFavoritePage();
    void sl_searchInPage(QString str);
    int sl_openFavorite();

signals:
    void sig_canGoBack();
    void sig_noBack();
    void sig_canGoNext();
    void sig_noNext();
    void sig_preferredPage();
    void sig_notPreferredPage();
};

#endif // SASAKI_H
