#include "StatusBar.h"
#include <QPushButton>

//-------------------------------------------------------------------------

StatusBar::StatusBar(QWidget *parent): QStatusBar(parent),
    m_progressLabel(nullptr),
    m_loadProgress(nullptr)
{
    m_progressLabel = new QLabel(this);
    m_loadProgress = new QProgressBar(this);

    SconfigureStatusProgress();

    addPermanentWidget(m_progressLabel, 1000);
    addPermanentWidget(m_loadProgress, 1000);
}

//-------------------------------------------------------------------------

StatusBar::~StatusBar()
{
    std::cout << "StatusBar destroyed\n";
}

//-------------------------------------------------------------------------

QProgressBar *StatusBar::get_m_progressBar()
{
    return m_loadProgress;
}

//-------------------------------------------------------------------------

QLabel *StatusBar::get_m_progressLabel()
{
    return m_progressLabel;
}

//-------------------------------------------------------------------------

void StatusBar::SconfigureStatusProgress()
{
    m_progressLabel->setVisible(false);

    // = = = = = = = = = = = = = = = = = = = = =

    m_loadProgress->setValue(50);
    m_loadProgress->setTextVisible(false);
    m_loadProgress->setVisible(false);
    m_loadProgress->setMaximumSize(1000, 10);
}

//-------------------------------------------------------------------------


