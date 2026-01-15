#ifndef SETTINGS_H
#define SETTINGS_H

// = = = = C++
#include <iostream>

// = = = = Qt
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QGroupBox>


class Settings: public QDialog
{
public:
    Settings(QWidget *parent = nullptr);
    ~Settings();

    bool initialiseProperties();

protected:
    QVBoxLayout *m_mainLayout;
    QScrollArea *m_scroll;
    QGroupBox *m_groupMainSettings;
    QGroupBox *m_essaie;
<<<<<<< HEAD
=======
    QGroupBox *m_autreEssaie;
>>>>>>> 9939f7f (adding a QGroupBox)
    
    //this is nothing


};

#endif // SETTINGS_H
