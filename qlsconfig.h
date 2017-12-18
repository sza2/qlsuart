#ifndef QLSCONFIG_H
#define QLSCONFIG_H

#include <QDialog>

namespace Ui {
class qlsconfig;
}

class qlsconfig : public QDialog
{
    Q_OBJECT

public:
    explicit qlsconfig(QWidget *parent = 0);
    ~qlsconfig();
    QString getCmd0();
    QString getCmd1();
    QString getCmd2();

    void setCmd0(QString text);
    void setCmd1(QString text);
    void setCmd2(QString text);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::qlsconfig *ui;
};

#endif // QLSCONFIG_H
