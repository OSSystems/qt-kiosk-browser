/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */


#include <QtQml/qqml.h>
#include <QtWebEngineQuick/qtwebenginequickglobal.h>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtGui/QGuiApplication>

#include "inputeventhandler.hpp"
#include "browser.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("QT kiosk browser");

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qputenv("QML_XHR_ALLOW_FILE_READ", QByteArray("1"));
    
    QtWebEngineQuick::initialize();

    QGuiApplication app(argc, argv);

    qmlRegisterSingletonType<InputEventHandler>("Browser", 1, 0, "Browser", [](QQmlEngine *, QJSEngine *) -> QObject * {
        return new Browser();
    });
    qmlRegisterType<InputEventHandler>("Browser", 1, 0, "InputEventHandler");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
