/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */

#include <QApplication>
#include <QtWebEngine>

#include "inputeventhandler.hpp"
#include "browser.hpp"

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QtWebEngine::initialize();

    qmlRegisterSingletonType<InputEventHandler>("Browser", 1, 0, "Browser", [](QQmlEngine *, QJSEngine *) -> QObject * {
        return new Browser();
    });
    qmlRegisterType<InputEventHandler>("Browser", 1, 0, "InputEventHandler");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}
