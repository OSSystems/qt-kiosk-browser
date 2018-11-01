#include "browser.hpp"

#include <QProcess>

Browser::Browser(QObject *parent): QObject(parent)
{
}

void Browser::restart()
{
    QProcess::startDetached("systemctl", QStringList() << "restart" << "browser");
}
