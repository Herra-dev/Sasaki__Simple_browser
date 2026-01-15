#include <Sasaki.h>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QSettings>
#include <QStringList>

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_UseSoftwareOpenGL);
    QCoreApplication::setOrganizationName("Carotte");
    QCoreApplication::setApplicationName("Sasaki");

    QApplication app(argc, argv);

    Sasaki saki;
    saki.show();

    return app.exec();
}
