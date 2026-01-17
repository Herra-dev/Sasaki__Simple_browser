#include "Sasaki.h"
#include <QSettings>


#define SUCCESS 0
#define FAILURE -1
#define SEPARATOR "-url:"

///----------------------------------------------------------------------

/**
 * @brief Sasaki::Sasaki: * * * constructor
 * @param parent
 */
Sasaki::Sasaki(QWidget *parent): QMainWindow(parent),
    m_navigationMenu(nullptr),
    m_settingMenu(nullptr),
    m_aboutMenu(nullptr),
    m_recentLinkSubMenu(nullptr),
    m_actionFind(nullptr),
    m_actionCloseTab(nullptr),
    m_actionCloseAllTab(nullptr),
    m_actionPreviousPage(nullptr),
    m_actionNextPage(nullptr),
    m_actionReloadPage(nullptr),
    m_actionHome(nullptr),
    m_actionCancel(nullptr),
    m_actionLaunch(nullptr),
    m_actionPreferedPage(nullptr),
    m_actionQuit(nullptr),
    m_actionHistory(nullptr),
    m_actionClearHistory(nullptr),
    m_actionFavorite(nullptr),
    m_toolBar(nullptr),
    m_urlEdit(nullptr),
    m_searchEdit(nullptr),
    m_centralZone(nullptr),
    m_centralWidget(nullptr),
    m_subWindow1(nullptr),
    m_layout(nullptr),
    m_buttonNewTab(nullptr),
    m_tabView(nullptr),
    m_statusBar(nullptr),
    history(nullptr)
{
    ScreateWidget();
    SconfigureWidget();

    ///--------- menu bar - tool bar
    SaddMenu();
    ScreateAction();
    SconfigureAction();
    SaddActionToMenu();
    SconnectAction();
    SaddToolBar();
    SaddActionToToolBar();

    ///--------- central zone
    ScreateCentralWidget();
    SconfigureCentralWidget();
    SsetCentralWidget();
    ScreateSubWindow();
    SconfigureSubWindow();
    SaddWidgetToCentralLayout();
    SconnectWidget();

    ///--------- status bar
    ScreateStatusBar();
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::~Sasaki
 */
Sasaki::~Sasaki()
{
    std::cout << "Saki destroyed\n";
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::get_currentWebView
 * @return QWebEngineView - the current QWebEngineView shown to user if page is not empty, otherwise returns nullptr
 */
QWebEngineView *Sasaki::get_currentWebView()
{
    return (!(page.empty()) ? page.at(m_tabView->currentIndex())->get_m_view() : nullptr);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::get_currentIndex
 * @return int - the current m_tabView(QTabWidget)'s index shown to user if page is not empty, otherwise returns -1
 */
int Sasaki::get_currentIndex()
{
    return (!(page.empty()) ? m_tabView->currentIndex() : -1);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::get_currentWebViewIndex
 * @return int - the current QWebEngineView's index shown to user if page is not empty, otherwise returns -1
 */
int Sasaki::get_currentWebViewIndex()
{
    return (!page.empty()) ? page.at(m_tabView->currentIndex())->get_m_objectId() : -1;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::get_currentWebViewHistory
 * @return QWebEngineHistory -  the current QWebEngineView's history if page is not empty, otherwise returns nullptr
 */
QWebEngineHistory *Sasaki::get_currentWebViewHistory()
{
    return (!page.empty()) ? get_currentWebView()->history() : nullptr;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SemitSignal
 *
 */
void Sasaki::SemitSignal()
{
    if(page.size() < 1) //if there is no page yet, quit function
        return;

    if(get_currentWebViewHistory()->canGoBack())
        emit sig_canGoBack();
    if(!(get_currentWebViewHistory()->canGoBack()))
        emit sig_noBack();
    if(get_currentWebViewHistory()->canGoForward())
        emit sig_canGoNext();
    if(!(get_currentWebViewHistory()->canGoForward()))
        emit sig_noNext();

    std::cout << "signal emitter called" << std::endl;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SaddMenu
 *
 * adding some menuBar to the app
 */
void Sasaki::SaddMenu()
{
    m_navigationMenu = menuBar()->addMenu(tr("&Navigation"));
    m_settingMenu = menuBar()->addMenu(tr("&Setting"));
    m_aboutMenu = menuBar()->addMenu(tr("&About"));
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::ScreateSubMenu
 *
 * adding a subMenu to the app
 */
void Sasaki::ScreateNavigationSubMenu()
{
    m_recentLinkSubMenu = m_navigationMenu->addMenu("Recent");
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SaddToSubMenu
 *
 * adding QAction to m_recentLinkSubMenu
 */
void Sasaki::SaddActionToNavigationSubMenu()
{
    int limit = 0;
    QString string;
    string.clear();

    m_recentLinkSubMenu->clear(); // clear the sub menu
    title.erase(title.begin(), title.end()); // erase all existing QAction in m_recentLinkSubMenu

    QFile *read = new QFile("assets/file/history.txt", this);
    read->open(QIODeviceBase::ReadOnly, QFileDevice::ReadOwner);
    while((!(read->atEnd())) && limit < 10) // show only 10 links
    {
        string = read->readLine();
        if(string.isEmpty())
        {
            std::cout << "empty" << std::endl;
            return;
        }

        title.push_back(new QAction(SfirstString(string), this));
        m_recentLinkSubMenu->addAction(title.back());

        QObject::connect(title.back(), &QAction::triggered, this, [=]() { this->sl_runUrl(SlastString(string)); });

        limit++;
    }

    read->close();
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SfirstString
 * @param string
 * @return the first part of a string separated by SEPARATOR
 */
QString Sasaki::SfirstString(QString string) // static method
{
    return string.sliced(0, string.indexOf(SEPARATOR)).simplified();
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SlastString
 * @param string
 * @return the last part of a string separated by SEPARATOR
 */
QString Sasaki::SlastString(QString string) // static method
{
    QString st = SEPARATOR;

    return string.sliced(string.indexOf(st) + st.size()).simplified(); //Returns a string that has whitespace removed from the start and the end,
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::createAction
 */
void Sasaki::ScreateAction()
{
    m_actionFind = new QAction(tr("&Find"), this);
    m_actionCloseTab = new QAction(tr("Close tab"), this);
    m_actionCloseAllTab = new QAction(tr("Close all tabs"), this);
    m_actionPreviousPage = new QAction(tr("Previous"), this);
    m_actionNextPage = new QAction(tr("Next"), this);
    m_actionReloadPage = new QAction(tr("Reload"), this);
    m_actionHome = new QAction(tr("Home"), this);
    m_actionCancel = new QAction(tr("Cancel"), this);
    m_actionLaunch = new QAction(tr("Launch"), this);
    m_actionPreferedPage = new QAction(tr("Favorite"), this);
    m_actionQuit = new QAction(tr("Quit"), this);
    m_actionHistory = new QAction(tr("&History"), this);
    m_actionClearHistory = new QAction(tr("Clear history"), this);
    m_actionFavorite = new QAction(tr("&Favorite page"), this);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::configureAction
 */
void Sasaki::SconfigureAction()
{
    m_actionFind->setShortcut(QKeySequence(tr("alt+shift+F")));
    m_actionFind->setIcon(QIcon("assets/icons/find.png"));

    m_actionCloseTab->setShortcut(QKeySequence(tr("del")));
    m_actionCloseTab->setIcon(QIcon("assets/icons/delTab.png"));

    m_actionCloseAllTab->setIcon(QIcon("assets/icons/clear.png"));

    m_actionPreviousPage->setIcon(QIcon("assets/icons/noPrevious.png"));

    m_actionNextPage->setIcon(QIcon("assets/icons/noNext.png"));

    m_actionReloadPage->setShortcut(QKeySequence(tr("f5")));
    m_actionReloadPage->setIcon(QIcon("assets/icons/reload.png"));

    m_actionHome->setIcon(QIcon("assets/icons/home.png"));

    m_actionCancel->setIcon(QIcon("assets/icons/cancel.png"));

    m_actionLaunch->setShortcut(QKeySequence(tr("Enter")));
    m_actionLaunch->setIcon(QIcon("assets/icons/launch.png"));

    m_actionPreferedPage->setIcon(QIcon("assets/icons/star.png"));
    m_actionPreferedPage->setCheckable(true);
    m_actionPreferedPage->setEnabled(false);

    m_actionQuit->setShortcut(QKeySequence(tr("alt+f4")));
    m_actionQuit->setIcon(QIcon("assets/icons/quit.png"));

    m_actionHistory->setIcon(QIcon("assets/icons/history.png"));

    m_actionClearHistory->setIcon(QIcon("assets/icons/clearHistory.png"));

    m_actionFavorite->setShortcut(QKeySequence(tr("ctrl+shift+t")));
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SaddAction
 */
void Sasaki::SaddActionToMenu()
{
    {
        m_navigationMenu->addAction(m_actionFind);
        ScreateNavigationSubMenu();
        SaddActionToNavigationSubMenu();
        m_navigationMenu->addAction(m_actionCloseTab);
        m_navigationMenu->addAction(m_actionCloseAllTab);
        m_navigationMenu->addAction(m_actionPreviousPage);
        m_navigationMenu->addAction(m_actionNextPage);
        m_navigationMenu->addAction(m_actionReloadPage);
        m_navigationMenu->addAction(m_actionHome);
        m_navigationMenu->addAction(m_actionCancel);
        m_navigationMenu->addAction(m_actionLaunch);
        m_navigationMenu->addAction(m_actionPreferedPage);
        m_navigationMenu->addAction(m_actionQuit);
    }

    /// = = = = = = = = = = = = = = = = = = = = = = = = = =

    {
        m_settingMenu->addAction(m_actionHistory);
        m_settingMenu->addAction(m_actionClearHistory);
        m_settingMenu->addAction(m_actionFavorite);
    }
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SconnectAction
 */
void Sasaki::SconnectAction()
{
    QObject::connect(m_actionQuit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    QObject::connect(m_actionCloseTab, SIGNAL(triggered(bool)), this, SLOT(sl_removeTab()));
    QObject::connect(m_actionCloseAllTab, SIGNAL(triggered(bool)), this, SLOT(sl_removeAllTabs()));
    QObject::connect(m_actionPreviousPage, SIGNAL(triggered(bool)), this, SLOT(sl_back()));
    QObject::connect(m_actionNextPage, SIGNAL(triggered(bool)), this, SLOT(sl_next()));
    QObject::connect(m_actionReloadPage, SIGNAL(triggered(bool)), this, SLOT(sl_reload()));
    QObject::connect(m_actionCancel, SIGNAL(triggered(bool)), this, SLOT(sl_cancelLoading()));
    QObject::connect(m_actionHome, SIGNAL(triggered(bool)), this, SLOT(sl_returnHome()));
    QObject::connect(m_actionLaunch, SIGNAL(triggered(bool)), this, SLOT(sl_runUrl()));
    QObject::connect(m_actionPreferedPage, SIGNAL(toggled(bool)), this, SLOT(sl_addPageToFavorite(bool)));
    QObject::connect(m_actionPreferedPage, SIGNAL(toggled(bool)), this, SLOT(sl_removePageFromFavorite(bool)));
    QObject::connect(this, SIGNAL(sig_preferredPage()), this, SLOT(sl_favoritePage()));
    QObject::connect(this, SIGNAL(sig_notPreferredPage()), this, SLOT(sl_notFavoritePage()));

    QObject::connect(m_actionHistory, SIGNAL(triggered(bool)), this, SLOT(sl_openHistory()));
    QObject::connect(m_actionClearHistory, SIGNAL(triggered(bool)), this, SLOT(sl_clearHistory()));
    QObject::connect(m_actionFavorite, SIGNAL(triggered(bool)), this, SLOT(sl_openFavorite()));
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SaddToolBar
 */
void Sasaki::SaddToolBar()
{
    m_toolBar = addToolBar("Tool Bar");
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SaddActionToToolBar
 */
void Sasaki::SaddActionToToolBar()
{
    m_toolBar->addAction(m_actionQuit);
    m_toolBar->addAction(m_actionPreviousPage);
    m_toolBar->addAction(m_actionNextPage);
    m_toolBar->addAction(m_actionReloadPage);
    m_toolBar->addAction(m_actionHome);
    m_toolBar->addAction(m_actionCancel);
    m_toolBar->addWidget(m_urlEdit);
    m_toolBar->addAction(m_actionLaunch);
    m_toolBar->addAction(m_actionPreferedPage);
    m_toolBar->addWidget(m_searchEdit);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::ScreateWidget
 */
void Sasaki::ScreateWidget()
{
    m_urlEdit = new QLineEdit(this);
    m_searchEdit = new QLineEdit(this);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SconfigureWidget
 */
void Sasaki::SconfigureWidget()
{
    m_searchEdit->setFixedWidth(90);
    m_searchEdit->setToolTip("search here");
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::ScreateCentralWidget
 */
void Sasaki::ScreateCentralWidget()
{
    m_centralZone = new QMdiArea(this);
    m_centralWidget = new QWidget(this);
    m_layout = new QVBoxLayout(m_centralWidget);
    m_buttonNewTab = new QPushButton("+", this);
    m_tabView = new QTabWidget(this);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SconfigureCentralWidget
 */
void Sasaki::SconfigureCentralWidget()
{
    m_centralWidget->setLayout(m_layout);

    m_tabView->setTabsClosable(true);
    m_tabView->setMovable(true);
    m_tabView->setUsesScrollButtons(true);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SsetCentralWidget
 */
void Sasaki::SsetCentralWidget()
{
    setCentralWidget(m_centralZone);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::ScreateSubWindow
 */
void Sasaki::ScreateSubWindow()
{
    m_subWindow1 = m_centralZone->addSubWindow(m_centralWidget);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SconfigureSubWindow
 */
void Sasaki::SconfigureSubWindow()
{
    m_subWindow1->showMaximized();
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SaddWidgetToCentralLayout
 */
void Sasaki::SaddWidgetToCentralLayout()
{
    m_layout->addWidget(m_buttonNewTab);
    m_layout->addWidget(m_tabView);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SconnectWidget
 */
void Sasaki::SconnectWidget()
{
    QObject::connect(m_buttonNewTab, SIGNAL(clicked(bool)), this, SLOT(sl_addNewTab()));
    QObject::connect(m_tabView, SIGNAL(tabCloseRequested(int)), this, SLOT(sl_removeTab(int)));
    QObject::connect(m_tabView, SIGNAL(currentChanged(int)), this, SLOT(sl_tabChanged(int)));
    QObject::connect(m_searchEdit, SIGNAL(textChanged(QString)), this, SLOT(sl_searchInPage(QString)));
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SconnectDependentWidgAct
 */
void Sasaki::SconnectDependentWidgAct()
{
    QObject::connect(get_currentWebView(), SIGNAL(urlChanged(QUrl)), this, SLOT(sl_urlChanged(QUrl)));
    QObject::connect(get_currentWebView(), SIGNAL(titleChanged(QString)), this, SLOT(sl_titleChanged(QString)));
    QObject::connect(get_currentWebView(), SIGNAL(loadStarted()), this, SLOT(sl_loadStarted()));
    QObject::connect(get_currentWebView(), SIGNAL(loadFinished(bool)), this, SLOT(sl_loadFinished(bool)));
    QObject::connect(get_currentWebView(), SIGNAL(loadProgress(int)), this, SLOT(sl_progress(int)));
    QObject::connect(this, SIGNAL(sig_canGoBack()), this, SLOT(sl_canGoBack()));
    QObject::connect(this, SIGNAL(sig_noBack()), this, SLOT(sl_noBack()));
    QObject::connect(this, SIGNAL(sig_canGoNext()), this, SLOT(sl_canGoNext()));
    QObject::connect(this, SIGNAL(sig_noNext()), this, SLOT(sl_noNext()));
    QObject::connect(get_currentWebView(), SIGNAL(iconChanged(QIcon)), this, SLOT(sl_iconChanged(QIcon)));
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::ScreateStatusBar
 */
void Sasaki::ScreateStatusBar()
{
    m_statusBar = new StatusBar(this);
    setStatusBar(m_statusBar);
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::SReadWriteHistory
 *
 * used to write history to the history file txt
 */
void Sasaki::SReadWriteHistory()
{
    QFile *read = new QFile("assets/file/history.txt", this);
    QString st;

    if((read->open(QIODeviceBase::ReadWrite))) // opening the history file with mode ReadWrite
    {
        st = read->readAll(); // read all data of the file and copy these data to st(QString)

        std::cout << "history saved" << std::endl;

        read->close(); // close the file
    }
    else
        return;

    delete read;
    read = nullptr;

    // = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =


    QFile *write = new QFile("assets/file/history.txt", this);

    std::cout << "history saved" << std::endl;
    if(write->open(QIODeviceBase::WriteOnly)) // opening the history file with mode WriteOnly
    {
        if(write->isOpen())
        {
            QTextStream *out = new QTextStream(write);
            *out << get_currentWebView()->title() << SEPARATOR << get_currentWebView()->url().toString() << "\n"; // write the QWebEngineView's title and url in the history file using an Object QTextStream out
            *out << st;

            delete out;
            out = nullptr;

            write->close(); // close the history file
        }
    }
    else
        return;

    delete write;
    write = nullptr;

}

///----------------------------------------------------------------------

bool Sasaki::isPreferred()
{
    if(page.size() < 1)
        return false;

    QFile *read = new QFile("assets/file/star.txt", this);
    if(!(read->open(QIODeviceBase::ReadOnly)))
    {
        return false;
    }

    QString str;
    str.clear();

    str = read->readAll(); // save all content of read into str(QString)

    read->close();

    delete read;
    read = nullptr;

    std::cout << "switched to webView: " << get_currentWebViewIndex() << std::endl;

    if(str.contains(get_currentWebView()->url().toString().simplified()))
    {
        emit sig_preferredPage();
        std::cout << "This is a preferred page" << std::endl;
        return true;
    }

    else
    {
        emit sig_notPreferredPage();
        std::cout << "This is not a preferred page" << std::endl;
        return false;
    }
}

///----------------------------------------------------------------------

void Sasaki::SloadSetings()
{
    if(page.size() < 1) // if there is no page yet, quit fuction
        return;

    QSettings saki_settings;

    get_currentWebView()->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, saki_settings.value("web/JavascriptEnabled").toBool());
}

///----------------------------------------------------------------------

///======================================================================================
///===================== PUBLIC SLOTS ===================================================
///======================================================================================

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_newTab
 * @return: 0 if a tab was added, -1 otherwise
 *
 */
int Sasaki::sl_addNewTab()
{
    int begin = m_tabView->count();
    int last = 0;

    page.push_back(new WebView(this)); //adding a WebView to page
    std::cout << "--> new WebView object added to page" << std::endl;

    m_tabView->addTab(page.back(), tr("New Tab")); // adding a widget --> WebView as a tab to m_tabView with 'New Tab' as title

    m_tabView->setCurrentWidget(page.back()); // Show the new tab

    if(m_urlEdit->text().isEmpty()) // if the QLineEdit is empty, take the default url (index.html) as url
        m_urlEdit->setText(get_currentWebView()->url().toString());

    last = m_tabView->count();

    SconnectDependentWidgAct();
    std::cout << "begin = " << begin << ", last = " << last << std::endl;

    m_actionPreferedPage->setEnabled(true);

    return (begin != last) ? SUCCESS : FAILURE; // if begin is different of last, certainly: a tab was added
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_removeTab
 * @param index
 * @return 0 if a tab at index @param index was removed, -1 otherwise
 */
int Sasaki::sl_removeTab(const int index)
{
    std::cout << "requesting to remove a tab at index " << index << std::endl;

    if(index < 0) // if there is no tab yet, quit application
    {
        qApp->quit();
        return FAILURE;
    }

    int pageSize = page.size();

    if(pageSize > 1) // test if there is more tab than 1
    {
        m_tabView->removeTab(index); // remove the tab at index -> index

        WebView *temp = page[index]; // store the object we wish to erase into pointer temp

        page.erase(page.begin() + index); // erase the WebView from page

        delete temp; // erase the WebView(temp) from memory
        temp = nullptr; //pointing temp to "nullptr"

        int currentIndex = get_currentIndex();
        m_tabView->setCurrentWidget(page[0]); // switched quickly to webView at index 0

        m_tabView->setCurrentWidget(page[currentIndex]);

        std::cout << "tab removed successfully" << std::endl;
        return SUCCESS; // returning 0 if a tab was removed
    }
    else //only one tab left, return FAILURE (-1)
    {
        std::cout << "cannot remove the only one left tab" << std::endl;
        return FAILURE;
    }
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_removeTab
 * @return 0 if a tab at index currentIndex was removed, -1 otherwise
 */
int Sasaki::sl_removeTab()
{
    return sl_removeTab(get_currentIndex());
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_tabChanged
 * @param index
 * @return 0 if no problem encountered, -1 otherwise
 */
int Sasaki::sl_tabChanged(const int index)
{
    if(index == get_currentIndex() && page.size() > 1) // test if the index send by signal is equals to the current index and there is at least 2 tabs
    {
        m_urlEdit->setText(get_currentWebView()->url().toString());
        get_currentWebView()->show();
        std::cout << "signal --- changing tab detected \"urledit\" switched to " << get_currentWebView()->url().toString().toStdString() << std::endl;
        std::cout << "WebView number " << get_currentWebViewIndex() << " used" << std::endl;

        SemitSignal();
        isPreferred();

        return SUCCESS;
    }

    return FAILURE;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_removeAllTabs
 * @return 0 if no problem was encountered
 */
int Sasaki::sl_removeAllTabs()
{
    int pageSize = page.size();
    while(sl_removeTab(pageSize - 1) == SUCCESS) pageSize--; // continue until a FAILURE(cannot remove any tab)
    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_urlChanged
 * @param url
 * @return 0 if no problem was encountered
 */
int Sasaki::sl_urlChanged(const QUrl url)
{
    if(page.size() < 1)
        return FAILURE;

    std::cout << "signal url changed" << std::endl;
    m_urlEdit->setText(url.toString());

    SemitSignal();
    isPreferred();

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_runUrl
 * @return -1 if there is no tab, 0 if no problem was encountered
 *
 * if there is no url set, quit function - return FAILURE
 * if there is an url but no tab, add new tab then run url
 * if there is a tab and url, run url
 */
int Sasaki::sl_runUrl()
{
    if(m_urlEdit->text().isEmpty())
        return FAILURE;

    if(m_tabView->count() > 0)
    {
        get_currentWebView()->setUrl(QUrl(m_urlEdit->text()));
        get_currentWebView()->show();
    }
    else // if there is no tab yet, add new tab then run url
    {
        sl_addNewTab();
        sl_runUrl();
    }

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_titleChanged
 * @param title
 * @return -1 if there is no tab, 0 if no problem was encountered
 */
int Sasaki::sl_titleChanged(const QString title)
{
    if(page.size() < 1)
        return FAILURE;

    std::cout << "signal title changed" << std::endl;
    m_tabView->setTabText(get_currentIndex(), title); // change current widget title

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_back
 * @return -1 if there is no tab, 0 if no problem was encountered
 */
int Sasaki::sl_back()
{
    if(page.size() < 1)
        return FAILURE;

    get_currentWebView()->back();
    std::cout << "Back ..." << std::endl;

    get_currentWebView()->show();

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_next
 * @return -1 if there is no tab, 0 if no problem was encountered
 */
int Sasaki::sl_next()
{
    if(page.size() < 1)
        return FAILURE;

    get_currentWebView()->forward();
    std::cout << "forward ..." << std::endl;

    get_currentWebView()->show();

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_reload
 * @return -1 if there is no tab, 0 if no problem was encountered
 */
int Sasaki::sl_reload()
{
    if(page.size() < 1)
        return FAILURE;

    get_currentWebView()->reload();
    std::cout << "reloading ..." << std::endl;

    get_currentWebView()->show();

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_loadStarted
 * @return -1 if there is no tab, 0 if no problem was encountered
 */
int Sasaki::sl_loadStarted()
{
    if(page.size() < 1)
        return FAILURE;

    m_statusBar->get_m_progressLabel()->setText(get_currentWebView()->url().toString());
    m_statusBar->get_m_progressBar()->setVisible(true); // show the progress bar
    std::cout << "load started ..." << std::endl;

    m_statusBar->get_m_progressLabel()->setVisible(true);

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_loadFinished
 * @param ok
 * @return -1 if there is no tab, 0 if no problem was encountered
 *
 * if there is no page yet, quit function and returns -1
 * if
 */
int Sasaki::sl_loadFinished(const bool ok)
{
    if(page.size() < 1)
        return FAILURE;

    if(ok)
    {
        m_statusBar->get_m_progressLabel()->setVisible(false); // hide the progress label
        m_statusBar->get_m_progressBar()->setVisible(false); // Hide the progress bar
        std::cout << "load finished ..." << std::endl;
        m_tabView->setTabIcon(get_currentIndex(), QIcon("assets/icons/icon.png"));
    }

    SReadWriteHistory();
    SaddActionToNavigationSubMenu();
    isPreferred();
    sl_searchInPage(m_searchEdit->text());

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_progress
 * @param progress
 * @return -1 if there is no tab, 0 if no problem was encountered
 */
int Sasaki::sl_progress(int progress)
{
    if(page.size() < 1)
        return FAILURE;

    m_statusBar->get_m_progressLabel()->setText(get_currentWebView()->url().toString());
    m_statusBar->get_m_progressBar()->setValue(progress);

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_cancelLoading
 * @return -1 if there is no tab, 0 if no problem was encountered
 */
int Sasaki::sl_cancelLoading()
{
    if(page.size() < 1)
        return FAILURE;

    std::cout << "Stopping loading ..." << std::endl;
    get_currentWebView()->stop();
    std::cout << "Load stopped ." << std::endl;

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_canGoBack
 * @return 0 if no problem was encountered
 */
int Sasaki::sl_canGoBack()
{
    m_actionPreviousPage->setIcon(QIcon(tr("assets/icons/previous.png")));
    m_actionPreviousPage->setEnabled(true);
    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_noBack
 * @return 0 if no problem was encountered
 */
int Sasaki::sl_noBack()
{
    m_actionPreviousPage->setIcon(QIcon(tr("assets/icons/noPrevious.png")));
    m_actionPreviousPage->setEnabled(false);
    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_canGoNext
 * @return 0 if no problem was encountered
 */
int Sasaki::sl_canGoNext()
{
    m_actionNextPage->setIcon(QIcon(tr("assets/icons/next.png")));
    m_actionNextPage->setEnabled(true);
    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_noNext
 * @return 0 if no problem was encountered
 */
int Sasaki::sl_noNext()
{
    m_actionNextPage->setIcon(QIcon(tr("assets/icons/noNext.png")));
    m_actionNextPage->setEnabled(false);
    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_returnHome
 * @return 0 if no problem was encountered
 */
int Sasaki::sl_returnHome()
{
    if(page.size() < 1)
        return FAILURE;

    get_currentWebView()->setUrl(QUrl("http://localhost"));
    get_currentWebView()->show();

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_iconChanged
 * @param icon
 * @return 0 if title icon has changed, otherwise returns -1
 */
int Sasaki::sl_iconChanged(const QIcon icon)
{
    if(page.size() < 1) // if there is no page available, quit function and returns -1
        return FAILURE;

    std::cout << "Icon changed ..." << std::endl;

    m_tabView->setTabIcon(get_currentIndex(), icon);

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_runUrl
 * @param url
 * @return -1 in case of success.
 *
 * if there is no tab yet, add first a new tab then run url
 */
int Sasaki::sl_runUrl(QString url)
{
    if(m_tabView->count() > 0)
    {
        get_currentWebView()->setUrl(QUrl(url));
        get_currentWebView()->show();
    }
    else // if there is no tab yet, add new tab then run url
    {
        sl_addNewTab();
        sl_runUrl(url);
    }

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_openHistory
 * @return -1 if no history was found, otherwise run url and returns 0
 */
int Sasaki::sl_openHistory()
{
    History *stor = new History(this);
    stor->exec();

    if(stor->get_m_historyUrlToRun().toString().isEmpty())
    {
        delete stor;
        stor = nullptr;
        return FAILURE;
    }

    sl_runUrl(stor->get_m_historyUrlToRun().toString().simplified());

    delete stor;
    stor = nullptr;

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_clearHistory
 * @return -1 in case of error in opening history file, otherwise returns 0
 */
int Sasaki::sl_clearHistory()
{
    QFile *file = new QFile("assets/file/history.txt", this);
    if(!(file->open(QIODeviceBase::WriteOnly)))
        return FAILURE;

    file->remove(file->fileName());

    file->close();

    delete file;
    file = nullptr;

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_addPageFromFavorite
 * @param ok
 * @return 0 if the current page was added successfully from favorite, othewise returns -1
 *
 * possible errors:
 *      - no tab available
 *      - cannot open favorite text file
 */
int Sasaki::sl_addPageToFavorite(bool ok)
{
    QFile *read = new QFile("assets/file/star.txt", this);

    if(!ok || page.size() < 1 || !(read->open(QIODeviceBase::ReadWrite)))
    {
        delete read;
        read = nullptr;

        return FAILURE;
    }


    QString str;
    str.clear();

    while(!(read->atEnd())) // read all data in read
    {
        str = read->readAll(); // save all content of read into str(QString)
    }


    if(!(str.contains(get_currentWebView()->url().toString()))) // if the actual page is not already in prefered page, add it
    {
        QTextStream *out = new QTextStream(read);

        *out << get_currentWebView()->title() << SEPARATOR << get_currentWebView()->url().toString() << "\n";
        m_actionPreferedPage->setIcon(QIcon("assets/icons/yellowStar.png"));

        std::cout << "page added to favorite" << std::endl;
        delete out;
        out = nullptr;
    }

    read->close();

    delete read;
    read = nullptr;

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_removePageFromFavorite
 * @param ok
 * @return 0 if the current page was removed successfully from favorite, othewise returns -1
 *
 * possible error:
 *      - no tab available
 *      - cannot open favorite text file
 */
int Sasaki::sl_removePageFromFavorite(bool ok)
{
    QFile *read = new QFile("assets/file/star.txt", this);
    QFile *write = new QFile("assets/file/star.txt", this);

    // in case of error, delete read and write pointers, then quit function
    if(ok || page.size() < 1 || !(read->open(QIODeviceBase::ReadOnly)))
    {
        delete read;
        read = nullptr;

        delete write;
        write = nullptr;

        return FAILURE;
    }


    QString str;
    str.clear();

    while(!(read->atEnd())) // read all data in read
    {
        str = read->readAll(); // save all content of read into str(QString)
    }

    read->close();



    if(str.contains(get_currentWebView()->url().toString()) && write->open(QIODeviceBase::WriteOnly))
    {
        QString strToRemove = get_currentWebView()->title() + SEPARATOR + get_currentWebView()->url().toString() + "\n"; //page's title, SEPARATOR, page's url and line feed to remove

        str.remove(strToRemove);

        QTextStream *out = new QTextStream(write);

        *out << str;

        m_actionPreferedPage->setIcon(QIcon("assets/icons/star.png"));
        std::cout << "Page removed from favorite" << std::endl;

        delete out;
        out = nullptr;
    }
    write->close();

    return SUCCESS;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_favoritePage
 * @return 0 if the page is a favorite page
 */
bool Sasaki::sl_favoritePage()
{
    m_actionPreferedPage->setChecked(true);
    m_actionPreferedPage->setIcon(QIcon("assets/icons/yellowStar.png"));

    return true;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_notFavoritePage
 * @return 0 if the page is a favorite page
 */
bool Sasaki::sl_notFavoritePage()
{
    m_actionPreferedPage->setChecked(false);
    m_actionPreferedPage->setIcon(QIcon("assets/icons/star.png"));

    return false;
}

///----------------------------------------------------------------------

/**
 * @brief Sasaki::sl_searchInPage
 * @param str
 *
 * used to search str(QString) in the current WebView
 */
void Sasaki::sl_searchInPage(QString str)
{
    if(page.size() < 1)
        return;

    get_currentWebView()->findText(str);
}

///----------------------------------------------------------------------

int Sasaki::sl_openFavorite()
{
    Settings *st = new Settings(get_currentWebView(), this);
    st->exec();

//    if(st->get_m_urlToRun().toString().isEmpty())
//    {
//        delete st;
//        st = nullptr;
//        return FAILURE;
//    }

//    sl_runUrl(st->get_m_urlToRun().toString().simplified());


    delete st;
    st = nullptr;

    return SUCCESS;
}

