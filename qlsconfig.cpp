#include "qlsconfig.h"
#include "ui_qlsconfig.h"

qlsconfig::qlsconfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qlsconfig)
{
    ui->setupUi(this);
}

qlsconfig::~qlsconfig()
{
    delete ui;
}

void qlsconfig::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString qlsconfig::getCmd0()
{
    return ui->editCmd0->text();
}

QString qlsconfig::getCmd1()
{
    return ui->editCmd1->text();
}

QString qlsconfig::getCmd2()
{
    return ui->editCmd2->text();
}

void qlsconfig::setCmd0(QString text)
{
    return ui->editCmd0->setText(text);
}

void qlsconfig::setCmd1(QString text)
{
    return ui->editCmd1->setText(text);
}

void qlsconfig::setCmd2(QString text)
{
    return ui->editCmd2->setText(text);
}
