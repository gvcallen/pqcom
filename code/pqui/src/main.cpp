#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("PQUI");
    QApplication::setOrganizationName("Gary Allen");
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
