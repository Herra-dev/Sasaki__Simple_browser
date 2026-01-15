#ifndef SETTINGS_H
#define SETTINGS_H

// = = = = C++
#include <iostream>

// = = = = Qt
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QScrollArea>
#include <QSettings>
#include <QWebEngineView>
#include <QWebEngineSettings>
#include <QObject>
#include <QLabel>

class Settings: public QDialog
{
Q_OBJECT

public:
    Settings(QWebEngineView *page = nullptr, QWidget *parent = nullptr);
    ~Settings();

    void initialiseProperties();
    void configureGlobalWidgets();
    void configurePageSettings();
    void addWidgetToMainLayout();
    void addWidgetToSettingsLayout();
    void addWidgetToControlLayout();
    void addWidgetToSettingsPageLayout();
    void connectWidget();

protected:
    QWebEngineView *actualPage;

    QVBoxLayout *m_layout;

    QGroupBox *m_settingsGroup;
    QGroupBox *m_controlGroup;
    QVBoxLayout *m_settingsLayout;
    QHBoxLayout *m_controlLayout;

    QScrollArea *m_settingsPageScroll;
    QScrollArea *m_settingsAppScroll;
    QGroupBox *m_settingsPageGroup;
    QGroupBox *m_settingsAppGroup;
    QVBoxLayout *m_settingsPageLayout;
    QVBoxLayout *m_settingsAppLayout;

    //control
    QScrollArea *m_settingsLogScroll;
    QLabel *m_settingsLog;

    //page settings ---------------------------------------------------------------

    QCheckBox *m_checkAutoLoadImages;
    QCheckBox *m_checkJavascriptEnabled;
    QCheckBox *m_checkJavascriptCanOpenWindows;


    //---------------------------------------------------------------

public slots:
    void sl_autoLoadImages(bool checked);
    void sl_javascriptEnabled(bool checked);
    void sl_javascriptCanOpenWindows(bool checked);

};

#endif // SETTINGS_H
