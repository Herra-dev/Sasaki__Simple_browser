#ifndef HISTORY_H
#define HISTORY_H

// = = = = Locale

#include "Sasaki.h"

// = = = = C++
#include <iostream>

// = = = = Qt
#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QUrl>
#include <QList>
#include <QPushButton>
#include <QFile>
#include <QObject>
#include <QScrollArea>
#include <QGroupBox>
#include <QLabel>
#include <QFont>

class History: public QDialog
{
Q_OBJECT

public:
    History(QWidget *parent = nullptr);
    ~History();

    QUrl get_m_historyUrlToRun(); // accessor


    void updateHistory();
    bool clearHistory();

protected:
    QGroupBox *group;
    QUrl *m_historyUrlToRun;
    QVBoxLayout *m_layout;
    QScrollArea *scroll;
    QList<QPushButton *> title;

public slots:
    int sl_updateUrlToRun(QUrl url);
};

#endif // HISTORY_H
