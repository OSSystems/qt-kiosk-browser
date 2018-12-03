/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include "browser.hpp"

#include <QProcess>

Browser::Browser(QObject *parent): QObject(parent)
{
}

void Browser::restart()
{
    QProcess::startDetached("systemctl", QStringList() << "restart" << "browser");
}
