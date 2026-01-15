#ifndef STATUSBAR_H
#define STATUSBAR_H

/// = = = = = C++
#include <iostream>

/// = = = = = Qt
#include <QStatusBar>
#include <QProgressBar>
#include <QLabel>

class StatusBar: public QStatusBar
{
public:
    StatusBar(QWidget *parent = nullptr);
    ~StatusBar();

    QProgressBar *get_m_progressBar(); // accessor
    QLabel *get_m_progressLabel(); // accessor

    void SconfigureStatusProgress();

protected:
    QLabel *m_progressLabel;
    QProgressBar *m_loadProgress;
};

#endif // STATUSBAR_H
