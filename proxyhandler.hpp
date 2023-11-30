/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */


#ifndef PROXYHANDLER_HPP
#define PROXYHANDLER_HPP

#include <QObject>
#include <QNetworkProxy>
#include <QByteArray>
#include <QUrl>

class ProxyHandler : public QObject
{
    Q_OBJECT
public:
    void printCurrentProxySettings();
    Q_INVOKABLE void useSystemProxy();
};

#endif // PROXYHANDLER_HPP