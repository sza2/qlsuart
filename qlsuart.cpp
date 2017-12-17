#include "qlsuart.h"
#include "ui_qlsuart.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    ui->tblSerialPorts->setColumnCount(8);
    QFont widgetFont = ui->tblSerialPorts->font();
    QFontMetrics fm(widgetFont);

    int itemLocation = 0;
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("ttyACM000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("00000000000000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("Status00"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("Manufacturer00"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("CP2104 USB to UART Bridge Controller000000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("0x00000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("0x00000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("/dev/ttyACM00"));


    ui->tblSerialPorts->setRowCount(serialPortInfos.count());
    ui->tblSerialPorts->verticalHeader()->hide();
    this->setFixedWidth(
                ui->tblSerialPorts->columnWidth(0) +
                ui->tblSerialPorts->columnWidth(1) +
                ui->tblSerialPorts->columnWidth(2) +
                ui->tblSerialPorts->columnWidth(3) +
                ui->tblSerialPorts->columnWidth(4) +
                ui->tblSerialPorts->columnWidth(5) +
                ui->tblSerialPorts->columnWidth(6) +
                ui->tblSerialPorts->columnWidth(7) +
                8
                );

    const QString blankString = "N/A";
    QString description;
    QString manufacturer;
    QString serialNumber;
    QTableWidgetItem *pCell;

    int portCount = 0;

    for (const QSerialPortInfo &serialPortInfo : serialPortInfos) {
        int itemLocation = 0;
        description = serialPortInfo.description();
        manufacturer = serialPortInfo.manufacturer();
        serialNumber = serialPortInfo.serialNumber();

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(serialPortInfo.portName());

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(!serialNumber.isEmpty() ? serialNumber : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(serialPortInfo.isBusy() ? "Busy" : "Free");

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(!manufacturer.isEmpty() ? manufacturer : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(!description.isEmpty() ? description : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(serialPortInfo.hasVendorIdentifier() ? QString("0x%1").arg(serialPortInfo.vendorIdentifier(), 4, 16, QLatin1Char('0')) : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(serialPortInfo.hasProductIdentifier() ? QString("0x%1").arg(serialPortInfo.productIdentifier(), 4, 16, QLatin1Char('0')) : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(serialPortInfo.systemLocation());

        portCount++;
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
