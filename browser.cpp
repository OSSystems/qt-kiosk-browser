/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include "browser.hpp"

#include <QProcess>
#include <QFile>

Browser::Browser(QObject *parent): QObject(parent)
{
}

void Browser::restart()
{
    if (QFile::exists("/etc/inittab"))
        QProcess::startDetached("/etc/init.d/qt-kiosk-browser", QStringList() << "restart");
    else
        QProcess::startDetached("systemctl", QStringList() << "restart" << "qt-kiosk-browser");
}
