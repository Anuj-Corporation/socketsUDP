#include "conexion_1.h"
#include "ui_conexion_1.h"

//MACROS
#define localdir QHostAddress::LocalHost
#define puertolocal 1234

Conexion_1::Conexion_1(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Conexion_1)
{
    ui->setupUi(this);

    udpsocket = new QUdpSocket(this);
    udpsocket->bind(localdir,puertolocal);

    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(leerSocket()));

    ui->plainTextEdit->setReadOnly(true);
    ui->plainTextEdit->setPlainText("Ingrese la direccion IP y el puerto del par de conexion, separados por una coma  y despues de click en conectar:");
    ui->plainTextEdit->appendPlainText("Mi direccion es: " + QHostAddress(localdir).toString());
    ui->plainTextEdit->appendPlainText("Mipuerto es: " + QString("%1").arg(puertolocal));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(on_Enviar_clicked()));
}

Conexion_1::~Conexion_1()
{
    delete ui;
}

void Conexion_1::leerSocket()
{
    while (udpsocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(static_cast<int>( udpsocket->pendingDatagramSize()));
            QHostAddress sender;
            quint16 senderPort;

            udpsocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            ui->plainTextEdit->appendPlainText(QString(datagram));
    }
}

void Conexion_1::on_Conectar_clicked()
{
    ui->lcdNumber->setDigitCount(11);

    direccionPar= ui->lineEdit->text().section(',',0,0);

    puertoPar= static_cast<quint16>( ui->lineEdit->text().section(',',1,1).toInt() );

    ui->lcdNumber->display(direccionPar.toString());
    ui->lcdNumber_2->display(puertoPar);

    ui->lineEdit->clear();
    ui->plainTextEdit->clear();

}

void Conexion_1::on_Enviar_clicked()
{
    udpsocket->writeDatagram(ui->lineEdit->text().toLatin1(),direccionPar,puertoPar);
    ui->lineEdit->clear();
}
