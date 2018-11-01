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
