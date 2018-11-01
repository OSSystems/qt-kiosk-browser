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
