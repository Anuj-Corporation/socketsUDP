#include "conexion_2.h"
#include "ui_conexion_2.h"

//MACROS
#define localdir QHostAddress::LocalHost
#define puertolocal 1244

Conexion_2::Conexion_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Conexion_2)
{
    ui->setupUi(this);

    udpsocket = new QUdpSocket(this);
    udpsocket->bind(localdir,puertolocal);

    connect(udpsocket,SIGNAL(readyRead()),this,SLOT(leerSocket()));

    ui->plainTextEdit_2->setReadOnly(true);
    ui->plainTextEdit_2->setPlainText("Ingrese la direccion IP y el puerto del par de conexion, separados por una coma  y despues de click en conectar:");
    ui->plainTextEdit_2->appendPlainText("Mi direccion es: " + QHostAddress(localdir).toString());
    ui->plainTextEdit_2->appendPlainText("Mipuerto es: " + QString("%1").arg(puertolocal));

    connect(ui->lineEdit_2,SIGNAL(returnPressed()),this,SLOT(on_Enviar_2_clicked()));
}

Conexion_2::~Conexion_2()
{
    delete ui;
}

void Conexion_2::on_Conectar_2_clicked()
{
    ui->lcddir->setDigitCount(11);

    direccionPar= ui->lineEdit_2->text().section(',',0,0);

    puertoPar= static_cast<quint16>( ui->lineEdit_2->text().section(',',1,1).toInt() );

    ui->lcddir->display(direccionPar.toString());
    ui->lcdpuerto->display(puertoPar);

    ui->lineEdit_2->clear();
    ui->plainTextEdit_2->clear();
}

void Conexion_2::on_Enviar_2_clicked()
{
    udpsocket->writeDatagram(ui->lineEdit_2->text().toLatin1(),direccionPar,puertoPar);
    ui->lineEdit_2->clear();
}

void Conexion_2::leerSocket()
{
    while (udpsocket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(static_cast<int>( udpsocket->pendingDatagramSize()));
            QHostAddress sender;
            quint16 senderPort;

            udpsocket->readDatagram(datagram.data(), datagram.size(),
                                    &sender, &senderPort);

            ui->plainTextEdit_2->appendPlainText(QString(datagram));
    }
}
