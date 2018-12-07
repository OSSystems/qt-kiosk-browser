TEMPLATE = app

QT += qml quick core gui webengine webenginewidgets

CONFIG += c++11

TARGET = qt-kiosk-browser

HEADERS += \
  inputeventhandler.hpp \
  browser.hpp

SOURCES += \
  main.cpp \
  inputeventhandler.cpp \
  browser.cpp

RESOURCES += resources.qrc

target.path = $$PREFIX/bin

INSTALLS += target
