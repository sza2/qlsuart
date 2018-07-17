#ifndef QLSUART_H
#define QLSUART_H

#include <QWidget>
#include <QSerialPortInfo>
#include <QTimer>
#include <QProcess>
#include <QSettings>
#include <QCollator>
#include <QMenu>

#include "qlsconfig.h"

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

private slots:
    void OnRefreshTimerExpired();
    void OnCellDoubleClicked(int row, int col);
    void copyRequested();
    void OnConfigureClicked();

private:
    Ui::Widget *ui;
    QTimer *refreshTimer;
    qlsconfig *configDialog;
    QMenu *contextMenu;
};

#endif // QLSUART_H
