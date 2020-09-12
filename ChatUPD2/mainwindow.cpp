#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("CHAT 2");

    udpsocket = new QUdpSocket(this);
    udpsocket->bind(LOCAL_ADDR,LOCAL_PORT);

    ui->plainTextEdit->setReadOnly(true);

    ui->plainTextEdit->setPlainText("Enter the IP address and port of the connection pair, separated by a comma, and click connect:");
    ui->plainTextEdit->appendPlainText("My address is: " + QHostAddress(LOCAL_ADDR).toString());
    ui->plainTextEdit->appendPlainText("My port is: " + QString("%1").arg(LOCAL_PORT));

    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_bSend_clicked()));
    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(readInformationReceived()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readInformationReceived()
{
    while (udpsocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(static_cast<int>( udpsocket->pendingDatagramSize()));

        udpsocket->readDatagram(datagram.data(), datagram.size(),
                                &PairAddr, &PairPort);

        //ui->plainTextEdit->appendPlainText(QString(datagram + " [" + PairAddr.toString() + ", %1]").arg(PairPort));

        //! [Step 1] Splitting the string
        QStringList operands = QString(datagram).split(',', QString::SkipEmptyParts);

        //! [Step 2] Conversion to integer values
        bool ok;
        int op1 = operands.at(0).toInt(&ok, 10);
        if(ok == false) ui->plainTextEdit->setPlainText("Error in operand 1");

        int op2 = operands.at(1).toInt(&ok, 10);
        if(ok == false) ui->plainTextEdit->setPlainText("Error in operand 1");

        //! [Step 3] Operation
        int result = op1 * op2;

        ui->plainTextEdit->setPlainText(QString("Multiple of A x B = %1").arg(result));
    }

}


void MainWindow::on_bConnect_clicked()
{
    PairAddr = QHostAddress( ui->lineEdit->text().section(',',0,0) );

    PairPort = static_cast<quint16>( ui->lineEdit->text().section(',',1,1).toInt() );

    ui->labAddr->setText( PairAddr.toString());
    ui->labPort->setText( QString("%1").arg(PairPort) );

    ui->lineEdit->clear();
    ui->plainTextEdit->clear();
}

void MainWindow::on_bSend_clicked()
{
    udpsocket->writeDatagram(ui->lineEdit->text().toLatin1(),PairAddr,PairPort);
    ui->lineEdit->clear();
}
