/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#ifndef INPUTEVENTHANDLER_HPP
#define INPUTEVENTHANDLER_HPP

#include <QQuickItem>

class InputEventHandler: public QObject
{
    Q_OBJECT

public:
    explicit InputEventHandler(QQuickItem *parent = nullptr);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void triggered();
};

#endif // INPUTEVENTHANDLER_HPP
