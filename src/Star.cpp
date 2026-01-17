#include "Star.h"

Star::Star(QWidget *parent): QDialog(parent),
    m_urlToRun(nullptr),
    m_scroll(nullptr),
    m_group(nullptr),
    m_layout(nullptr)

{
    setWindowTitle("Favorite page(s)");
    setMinimumSize(500, 600);

    //initialise properties
    //read file
    //show file content

    initialiseProperties();
    updateStar();
    m_group->setLayout(m_layout);
    m_scroll->setWidget(m_group);

}

//-----------------------------------------------------------------------------

Star::~Star()
{
    delete m_urlToRun;
    m_urlToRun = nullptr;
}

//-----------------------------------------------------------------------------

QUrl Star::get_m_urlToRun()
{
    return (m_urlToRun != nullptr) ? *m_urlToRun : QUrl();
}

//-----------------------------------------------------------------------------

void Star::set_m_urlToRun(QUrl url)
{
    *m_urlToRun = url;

    std::cout << "history url to run : " << get_m_urlToRun().toString().toStdString() << std::endl;
}

//-----------------------------------------------------------------------------

bool Star::initialiseProperties()
{
    m_urlToRun = new QUrl;
    m_scroll = new QScrollArea(this);
    m_group = new QGroupBox("Favorite(s)", m_scroll); // setting m_scroll(QScrollArea) as parent of m_group(QGroupBox)
    m_layout = new QVBoxLayout(m_group); // setting m_group(QGroupBox) as parent of m_layout(QVBoxLayout)

    return true;
}

//-----------------------------------------------------------------------------

bool Star::updateStar()
{
    QString str;
    str.clear();

    QFile *read = new QFile("assets/file/star.txt", this);

    if(!(read->open(QIODeviceBase::ReadOnly, QFileDevice::ReadOwner))) // quit function if an error has occured (cannot open history file)
    {
        return false;
    }

    while(!(read->atEnd()))
    {
        str = read->readLine(); // Read one line
        m_title.push_back(new QPushButton(Sasaki::SfirstString(str).simplified(), this)); // add one QPushButton (part0 of the QString str as name) to the QVector title
        m_title.back()->setToolTip(Sasaki::SlastString(str).simplified()); // set part1 of the QString str as toolTip to the QPushButton previously added
        m_layout->addWidget(m_title.back()); // add the QPushButton to the main layout

        // connect previously added QPushButton to the slot occupying to update the url to run later
        QObject::connect(m_title.back(), &QPushButton::clicked, this, [=]()
        {
            this->set_m_urlToRun(QUrl(Sasaki::SlastString(str).simplified())); // update the url to run

            this->close(); // close History after entering into this slot
        });
    }

    read->close();
    return true;
}


