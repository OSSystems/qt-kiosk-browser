/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#ifndef BROWSER_HPP
#define BROWSER_HPP

#include <QObject>

class Browser: public QObject
{
    Q_OBJECT

public:
    Browser(QObject *parent = nullptr);

public slots:
    void restart();
};

#endif // BROWSER_HPP
