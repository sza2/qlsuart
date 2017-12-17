#ifndef QLSUART_H
#define QLSUART_H

#include <QWidget>
#include <QSerialPortInfo>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Widget *ui;
};

#endif // QLSUART_H
