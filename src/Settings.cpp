#include "Settings.h"

Settings::Settings(QWebEngineView *page, QWidget *parent): QDialog(parent), actualPage(page),
    m_layout(nullptr),
    m_settingsGroup(nullptr),
    m_controlGroup(nullptr),
    m_settingsLayout(nullptr),
    m_controlLayout(nullptr),
    m_settingsPageScroll(nullptr),
    m_settingsAppScroll(nullptr),
    m_settingsPageGroup(nullptr),
    m_settingsAppGroup(nullptr),
    m_settingsPageLayout(nullptr),
    m_settingsAppLayout(nullptr),
    m_settingsLogScroll(nullptr),
    m_settingsLog(nullptr),
    m_checkAutoLoadImages(nullptr),
    m_checkJavascriptEnabled(nullptr),
    m_checkJavascriptCanOpenWindows(nullptr)
{
    setWindowTitle("Settings");
    setFixedSize(500, 800);

    initialiseProperties();
    configureGlobalWidgets();
    configurePageSettings();
    addWidgetToMainLayout();
    addWidgetToSettingsLayout();
    addWidgetToControlLayout();
    addWidgetToSettingsPageLayout();
    connectWidget();
}

//------------------------------------------------------------------------

Settings::~Settings()
{
    delete actualPage;
    actualPage = nullptr;

    std::cout << "settings destroyed" << std::endl;
}

//------------------------------------------------------------------------

void Settings::initialiseProperties()
{
    m_layout = new QVBoxLayout(this);

    m_settingsGroup = new QGroupBox("Settings:", this);
    m_controlGroup = new QGroupBox("control", this);
    m_settingsLayout = new QVBoxLayout(m_settingsGroup);
    m_controlLayout = new QHBoxLayout(m_controlGroup);

    m_settingsPageScroll = new QScrollArea(m_settingsGroup);
    m_settingsAppScroll = new QScrollArea(m_settingsGroup);
    m_settingsPageGroup = new QGroupBox("Page", m_settingsPageScroll);
    m_settingsAppGroup = new QGroupBox("App", m_settingsAppScroll);
    m_settingsPageLayout = new QVBoxLayout(m_settingsPageGroup);
    m_settingsAppLayout = new QVBoxLayout(m_settingsAppGroup);

    m_settingsLogScroll = new QScrollArea(this);
    m_settingsLog = new QLabel(tr("Log: "));

    // PAGE SETTINGS =================================

    m_checkAutoLoadImages = new QCheckBox(tr("Auto load images"), this);
    m_checkJavascriptEnabled = new QCheckBox(tr("Enable Javascript"), this);
    m_checkJavascriptCanOpenWindows = new QCheckBox(tr("Allow Javascript to open windows"), this);
}

//------------------------------------------------------------------------

void Settings::configureGlobalWidgets()
{
    m_controlGroup->setFixedHeight(200);
}

//------------------------------------------------------------------------

void Settings::configurePageSettings()
{
    m_checkAutoLoadImages->setToolTip(tr("Automatically dowloads images for web pages"));
    m_checkJavascriptEnabled->setToolTip(tr("Enables the running of JavaScript programs"));
    m_checkJavascriptCanOpenWindows->setToolTip(tr("Allows JavaScript programs to open popup windows without user interaction"));
}

//------------------------------------------------------------------------

void Settings::addWidgetToMainLayout()
{
    m_layout->addWidget(m_settingsGroup);
    m_layout->addWidget(m_controlGroup);
}

//------------------------------------------------------------------------

void Settings::addWidgetToSettingsLayout()
{
    m_settingsLayout->addWidget(m_settingsPageScroll);
    m_settingsLayout->addWidget(m_settingsAppScroll);
}

//------------------------------------------------------------------------

void Settings::addWidgetToControlLayout()
{
    m_controlLayout->addWidget(m_settingsLogScroll);
    m_settingsLogScroll->setWidget(m_settingsLog);
}

//------------------------------------------------------------------------

void Settings::addWidgetToSettingsPageLayout()
{
    m_settingsPageLayout->addWidget(m_checkAutoLoadImages);
    m_settingsPageLayout->addWidget(m_checkJavascriptEnabled);
    m_settingsPageLayout->addWidget(m_checkJavascriptCanOpenWindows);
}

//------------------------------------------------------------------------

void Settings::connectWidget()
{
    QObject::connect(m_checkAutoLoadImages, SIGNAL(toggled(bool)), this, SLOT(sl_autoLoadImages(bool)));
    QObject::connect(m_checkJavascriptEnabled, SIGNAL(toggled(bool)), this, SLOT(sl_javascriptEnabled(bool)));
    QObject::connect(m_checkJavascriptCanOpenWindows, SIGNAL(toggled(bool)), this, SLOT(sl_javascriptCanOpenWindows(bool)));
}

//------------------------------------------------------------------------
//  PUBLIC SLOTS
//------------------------------------------------------------------------

void Settings::sl_autoLoadImages(bool checked)
{
    QSettings saki_settings;

    saki_settings.setValue("web/AutoLoadImages", checked);
    if(actualPage != nullptr)
        actualPage->settings()->setAttribute(QWebEngineSettings::AutoLoadImages, checked);
}

//------------------------------------------------------------------------

void Settings::sl_javascriptEnabled(bool checked)
{
    QSettings saki_settings;

    saki_settings.setValue("web/JavascriptEnabled", checked);
    if(actualPage != nullptr)
        actualPage->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, checked);
}

//------------------------------------------------------------------------

void Settings::sl_javascriptCanOpenWindows(bool checked)
{
    QSettings saki_settings;

    saki_settings.setValue("web/JavascriptCanOpenWindows", checked);
    if(actualPage != nullptr)
        actualPage->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows, checked);
}
