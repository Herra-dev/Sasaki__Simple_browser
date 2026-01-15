#include "Settings.h"

Settings::Settings(QWidget *parent): QDialog(parent),
    m_mainLayout(nullptr),
    m_scroll(nullptr),
    m_groupMainSettings(nullptr)
{
    setWindowTitle("Settings");
    setFixedSize(500, 800);

    initialiseProperties();

}

//------------------------------------------------------------------------

Settings::~Settings()
{
    std::cout << "settings destroyed" << std::endl;
}

//------------------------------------------------------------------------

bool Settings::initialiseProperties()
{
    m_mainLayout = new QVBoxLayout(this);
    m_scroll = new QScrollArea(this);
    m_groupMainSettings = new QGroupBox("Settings:" , this);

    return true;
}
