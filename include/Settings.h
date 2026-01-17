#ifndef SETTINGS_H
#define SETTINGS_H

// = = = = Locale
#include "Sasaki.h"
#include "Settings.h"

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
#include <QStringList>
#include <QFile>
#include <QList>

class Settings: public QDialog
{
Q_OBJECT

public:
    Settings(QWebEngineView *page = nullptr, QWidget *parent = nullptr);
    ~Settings();

    void initialiseProperties();
    void addWidgetToMainLayout();
    void addWidgetToSettingsLayout();
    void addWidgetToControlLayout();
    void addCheckBox();

    void loadSettings(QWebEngineView *page = nullptr);

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
    QList<QCheckBox *> m_checkBox;

    //---------------------------------------------------------------

public slots:
    void sl_setAttribute(QWebEngineSettings::WebAttribute attribute, QString key, bool checked);

};

#endif // SETTINGS_H
