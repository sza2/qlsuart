#include "qlsuart.h"
#include "ui_qlsuart.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    configDialog = new qlsconfig;

    QSettings settings("qlsuart", "qlsuart");
    if(settings.value("cmd0").isValid()) {
        configDialog->setCmd0(settings.value("cmd0").toString());
    }
    if(settings.value("cmd1").isValid()) {
        configDialog->setCmd1(settings.value("cmd1").toString());
    }
    if(settings.value("cmd2").isValid()) {
        configDialog->setCmd2(settings.value("cmd2").toString());
    }
    refreshTimer = new QTimer;
    ui->tblSerialPorts->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tblSerialPorts->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tblSerialPorts->setColumnCount(8);
    QFont widgetFont = ui->tblSerialPorts->font();
    QFontMetrics fm(widgetFont);

    int itemLocation = 0;
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("ttyACM00000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("0000000000000000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("Status0000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("Manufacturer0000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("CP2104 USB to UART Bridge Controller00000000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("0x0000000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("0x0000000"));
    ui->tblSerialPorts->setColumnWidth(itemLocation++, fm.width("/dev/ttyACM0000"));

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
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(OnRefreshTimerExpired()));
    connect(ui->tblSerialPorts, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(OnCellDoubleClicked(int,int)));
    refreshTimer->start(500);

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

void Widget::OnRefreshTimerExpired()
{
    QFont widgetFont = ui->tblSerialPorts->font();
    QFontMetrics fm(widgetFont);
    QCollator collator;
    collator.setNumericMode(true);

    auto serialPortInfos = QSerialPortInfo::availablePorts();
    std::sort(serialPortInfos.begin(), serialPortInfos.end(), [&collator](const QSerialPortInfo &s1, const QSerialPortInfo &s2)
    {
        return collator.compare(s1.portName(), s2.portName()) < 0;
    });

    ui->tblSerialPorts->setRowCount(serialPortInfos.count());

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
        pCell->setToolTip(serialPortInfo.portName());

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(!serialNumber.isEmpty() ? serialNumber : blankString);
        pCell->setToolTip(!serialNumber.isEmpty() ? serialNumber : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(serialPortInfo.isBusy() ? "Busy" : "Free");
        pCell->setToolTip(serialPortInfo.isBusy() ? "Busy" : "Free");

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(!manufacturer.isEmpty() ? manufacturer : blankString);
        pCell->setToolTip(!manufacturer.isEmpty() ? manufacturer : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(!description.isEmpty() ? description : blankString);
        pCell->setToolTip(!description.isEmpty() ? description : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(serialPortInfo.hasVendorIdentifier() ? QString("0x%1").arg(serialPortInfo.vendorIdentifier(), 4, 16, QLatin1Char('0')) : blankString);
        pCell->setToolTip(serialPortInfo.hasVendorIdentifier() ? QString("0x%1").arg(serialPortInfo.vendorIdentifier(), 4, 16, QLatin1Char('0')) : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(serialPortInfo.hasProductIdentifier() ? QString("0x%1").arg(serialPortInfo.productIdentifier(), 4, 16, QLatin1Char('0')) : blankString);
        pCell->setToolTip(serialPortInfo.hasProductIdentifier() ? QString("0x%1").arg(serialPortInfo.productIdentifier(), 4, 16, QLatin1Char('0')) : blankString);

        pCell = new QTableWidgetItem;
        ui->tblSerialPorts->setItem(portCount, itemLocation++, pCell);
        pCell->setText(serialPortInfo.systemLocation());
        pCell->setToolTip(serialPortInfo.systemLocation());

        ui->tblSerialPorts->setRowHeight(portCount, fm.height() + 4);

        portCount++;
    }
}

void Widget::OnCellDoubleClicked(int row, int col)
{
    Qt::KeyboardModifiers modifiers  = QApplication::queryKeyboardModifiers();
    QString portLocation = ui->tblSerialPorts->item(row, 7)->text();
    QString portName = ui->tblSerialPorts->item(row, 0)->text();
    QString portNumber = ui->tblSerialPorts->item(row, 0)->text().remove(QRegExp("[A-Za-z]"));
    QString commandLine;

    if(!(modifiers.testFlag(Qt::AltModifier) || modifiers.testFlag(Qt::ControlModifier) || modifiers.testFlag(Qt::ShiftModifier))) {
        commandLine = configDialog->getCmd0();
    }
    if(modifiers.testFlag(Qt::ControlModifier)){
        commandLine = configDialog->getCmd1();
    }
    if(modifiers.testFlag(Qt::ShiftModifier)){
        commandLine = configDialog->getCmd2();
    }

    if(commandLine.indexOf("{devicename}") != -1) {
        commandLine.replace("{devicename}", portName, Qt::CaseSensitive);
    }
    if(commandLine.indexOf("{devicelocation}") != -1) {
        commandLine.replace("{devicelocation}", portLocation, Qt::CaseSensitive);
    }
    if(commandLine.indexOf("{devicenumber}") != -1) {
        commandLine.replace("{devicenumber}", portNumber, Qt::CaseSensitive);
    }
    QProcess::startDetached(commandLine);
    ui->lineLastExecutedCommand->setText(commandLine);
}

void Widget::OnConfigureClicked()
{
    QString cmd0 = configDialog->getCmd0();
    QString cmd1 = configDialog->getCmd1();
    QString cmd2 = configDialog->getCmd2();
    configDialog->setModal(true);
    configDialog->exec();
    if(configDialog->result() == QDialog::Accepted) {
        QSettings settings("qlsuart", "qlsuart");
        settings.setValue("cmd0", configDialog->getCmd0());
        settings.setValue("cmd1", configDialog->getCmd1());
        settings.setValue("cmd2", configDialog->getCmd2());
    } else {
        configDialog->setCmd0(cmd0);
        configDialog->setCmd1(cmd1);
        configDialog->setCmd2(cmd2);
    }
}
