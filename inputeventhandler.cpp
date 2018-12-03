/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include "inputeventhandler.hpp"

#include <QApplication>

InputEventHandler::InputEventHandler(QQuickItem *parent): QObject(parent)
{
    QApplication::instance()->installEventFilter(this);
}

bool InputEventHandler::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
        emit triggered();
    }

    return QObject::eventFilter(obj, event);
}
