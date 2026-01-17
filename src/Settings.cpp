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
    m_settingsLog(nullptr)
{
    setWindowTitle("Settings");

    initialiseProperties();
    addWidgetToMainLayout();
    addWidgetToSettingsLayout();
    addWidgetToControlLayout();
    addCheckBox();
    loadSettings(actualPage);
}

//------------------------------------------------------------------------

Settings::~Settings()
{
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

void Settings::addCheckBox()
{
    QFile *readCheckBoxText = new QFile("assets/file/.checkBoxText", this);
    QFile *readCheckBoxToolTip = new QFile("assets/file/.webAttribute_toolTip", this);
    QFile *readWebAttribute = new QFile("assets/file/.webAttribute_key", this);

    if(!(readCheckBoxText->open(QIODeviceBase::ReadOnly)) ||
            !(readCheckBoxToolTip->open(QIODeviceBase::ReadOnly)) ||
                !(readWebAttribute->open(QIODeviceBase::ReadOnly))) // quit function if an error occured (cannot open checkBoxText or webAttribute_toolTip or webAttribute_key files)
    {
        readCheckBoxText->deleteLater();
        readCheckBoxToolTip->deleteLater();
        readWebAttribute->deleteLater();
        return;
    }

//========================================================

    QString strCheckBoxText;
    strCheckBoxText.clear();
    QString strCheckBoxToolTip;
    strCheckBoxToolTip.clear();
    QString strWebAttribute;
    strWebAttribute.clear();

    while(!(readCheckBoxText->atEnd())) // Read file until cursor reach the eof
    {
        strCheckBoxText = readCheckBoxText->readLine().simplified(); // Read one line
        strCheckBoxToolTip = readCheckBoxToolTip->readLine().simplified(); // Read one line

//============================ adding QCheckBox to m_settingsPageLayout ============================

        m_checkBox.push_back(new QCheckBox(Sasaki::SlastString(strCheckBoxText, "-"), this));
        if((QString::compare(Sasaki::SfirstString(strCheckBoxText, "-"), Sasaki::SfirstString(strCheckBoxToolTip, "-"))) == 0)
            m_checkBox.back()->setToolTip(Sasaki::SlastString(strCheckBoxToolTip, "-"));

        m_settingsPageLayout->addWidget(m_checkBox.back());

//============================ connections signals/slots ============================

        strWebAttribute = readWebAttribute->readLine().simplified();
        QWebEngineSettings::WebAttribute attribute(static_cast<QWebEngineSettings::WebAttribute>(Sasaki::SfirstString(strWebAttribute, "-").toInt()));
        QString key(Sasaki::SlastString(strWebAttribute, "-").simplified());

        connect(m_checkBox.back(), &QCheckBox::toggled, this, [=](bool checked)
        {
            this->sl_setAttribute(attribute, key, checked);
        });

    }
    m_settingsPageScroll->setWidget(m_settingsPageGroup);

//============================ CLOSE ALL QFiles=============================================
    readCheckBoxText->close();
    readCheckBoxToolTip->close();
    readWebAttribute->close();

    readCheckBoxText->deleteLater();
    readCheckBoxToolTip->deleteLater();
    readWebAttribute->deleteLater();
}

//------------------------------------------------------------------------
//  PUBLIC SLOTS
//------------------------------------------------------------------------

void Settings::sl_setAttribute(QWebEngineSettings::WebAttribute attribute, QString key, bool checked)
{
    QSettings saki_settings;

    saki_settings.setValue(key, checked);
    if(actualPage != nullptr)
        actualPage->settings()->setAttribute(attribute, checked);
}

//------------------------------------------------------------------------

void Settings::loadSettings(QWebEngineView *page)
{
    QSettings saki_settings;
    QFile *readWebAttribute = new QFile("assets/file/.webAttribute_key");

    if(!(readWebAttribute->open(QIODeviceBase::ReadOnly)))
            return;

    QStringList list(saki_settings.allKeys());
    QList<QString> keyTable;
    QList<QString> value;

    while(!readWebAttribute->atEnd())
    {
        QString str = readWebAttribute->readLine().simplified();
        keyTable.push_back(Sasaki::SlastString(str, "-").simplified());
        value.push_back(Sasaki::SfirstString(str, "-").simplified());
    }

    int i(0);

    while(i < keyTable.size())
    {
        if(list.contains(keyTable[i]))
        {
            bool on = saki_settings.value(keyTable[i]).toBool();

            m_checkBox[i]->setChecked(on);
            if(page != nullptr)
                page->settings()->setAttribute(static_cast<QWebEngineSettings::WebAttribute>(value[i].toInt()), on);
        }

        i++;
    }

    readWebAttribute->close();

    delete readWebAttribute;
    readWebAttribute = nullptr;
}
