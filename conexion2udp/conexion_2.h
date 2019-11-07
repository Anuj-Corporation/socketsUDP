#ifndef CONEXION_2_H
#define CONEXION_2_H

#include <QMainWindow>
#include <QHostAddress>
#include <QUdpSocket>

namespace Ui {
class Conexion_2;
}

class Conexion_2 : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Conexion_2(QWidget *parent = nullptr);
    ~Conexion_2();
    
private slots:
    void on_Conectar_2_clicked();

    void on_Enviar_2_clicked();

public slots:
    void leerSocket();

private:
    Ui::Conexion_2 *ui;
    QUdpSocket *udpsocket;
    QHostAddress direccionPar;
    quint16 puertoPar;
};

#endif // CONEXION_2_H
