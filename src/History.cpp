#include "History.h"

//---------------------------------------------------------------------------

History::History(QWidget *parent): QDialog(parent),
    group(nullptr),
    m_historyUrlToRun(nullptr),
    m_layout(nullptr),
    scroll(nullptr)
{
    setWindowTitle("History");
    setMinimumSize(400, 500);

    group = new QGroupBox("History", this);
    m_historyUrlToRun = new QUrl;
    m_layout = new QVBoxLayout(this);
    scroll = new QScrollArea(this);

    updateHistory();

    if(title.isEmpty()) // if no history was found
    {
        QLabel noHistoryFound("No history found");
        noHistoryFound.setFont(QFont("Times"));

        m_layout->addWidget(&noHistoryFound);
        std::cout << "No history" << std::endl;
    }

    group->setLayout(m_layout);

    scroll->setWidget(group);
}

//---------------------------------------------------------------------------

/**
 * @brief History::~History
 * destructor
 */
History::~History()
{
    delete m_historyUrlToRun;
    m_historyUrlToRun = nullptr;

    std::cout << "history destroyed" << std::endl;
}

//---------------------------------------------------------------------------

/**
 * @brief History::get_m_historyUrlToRun
 * @return QUrl object
 */
QUrl History::get_m_historyUrlToRun()
{
    return *m_historyUrlToRun;
}

//---------------------------------------------------------------------------

void History::updateHistory()
{
    QString str;
    str.clear();

    clearHistory(); // first, clear history (QPushButton)

    QFile *read = new QFile("assets/file/history.txt", this);
    if(!(read->open(QIODeviceBase::ReadOnly, QFileDevice::ReadOwner))) // quit function if an error occured (cannot open history file)
    {
        return;
    }

    while(!(read->atEnd())) // Read file until cursor reach the eof
    {
        str = read->readLine(); // Read one line
        title.push_back(new QPushButton(Sasaki::SfirstString(str).simplified(), this)); // add one QPushButton (part0 of the QString str as name) to the QVector title
        title.back()->setToolTip(Sasaki::SlastString(str).simplified()); // set part1 of the QString str as toolTip to the QPushButton previously added
        m_layout->addWidget(title.back()); // add the QPushButton to the main layout

        // connect previously added QPushButton to the slot occupying to update the url to run later
        QObject::connect(title.back(), &QPushButton::clicked, this, [=]()
        {
            this->sl_updateUrlToRun(QUrl(Sasaki::SlastString(str).simplified())); // update the url to run

            this->close(); // close History after entering into this slot
        });
    }

    //= = = = = = = = = = = = = = = = = = = = = = = = = = =



    read->close(); // close file
}

//---------------------------------------------------------------------------

bool History::clearHistory()
{
    if(title.count() <= 0)
        return false;

    while(title.count() > 0)
    {
        QPushButton *temp = title.takeLast();

        temp->deleteLater();
    }

    return true;
}

//---------------------------------------------------------------------------
//----------- SLOT
//---------------------------------------------------------------------------

int History::sl_updateUrlToRun(QUrl url)
{
    *m_historyUrlToRun = url;

    std::cout << "history url to run : " << get_m_historyUrlToRun().toString().toStdString() << std::endl;

    return EXIT_SUCCESS;
}
