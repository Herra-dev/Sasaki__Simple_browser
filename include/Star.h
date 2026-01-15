#ifndef STAR_H
#define STAR_H

// = = = = Locale
#include "Sasaki.h"

// = = = = C++
#include <iostream>

// = = = = Qt
#include <QDialog>
#include <QWidget>
#include <QFile>
#include <QList>
#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>
#include <QObject>
#include <QGroupBox>
#include <QScrollArea>

class Star: public QDialog
{
Q_OBJECT

public:
    Star(QWidget *parent = nullptr);
    ~Star();

    QUrl get_m_urlToRun(); //accessor
    void set_m_urlToRun(QUrl url);

    bool initialiseProperties();
    bool updateStar();

protected:
    QList<QPushButton *> m_title;
    QUrl *m_urlToRun;
    QScrollArea *m_scroll;
    QGroupBox *m_group;
    QVBoxLayout *m_layout;

};

#endif // STAR_H
