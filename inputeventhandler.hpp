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
