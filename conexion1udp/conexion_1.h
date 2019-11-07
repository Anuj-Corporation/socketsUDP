#ifndef CONEXION_1_H
#define CONEXION_1_H

#include <QMainWindow>
#include <QHostAddress>
#include <QUdpSocket>

namespace Ui {
class Conexion_1;
}

class Conexion_1 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Conexion_1(QWidget *parent = nullptr);
    ~Conexion_1();

public slots:
    void leerSocket();
    
private slots:
    void on_Conectar_clicked();
    void on_Enviar_clicked();

private:
    Ui::Conexion_1 *ui;
    QUdpSocket *udpsocket;
    QHostAddress direccionPar;
    quint16 puertoPar;
};

#endif // CONEXION_1_H
