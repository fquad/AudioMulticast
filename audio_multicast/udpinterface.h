#ifndef UDPINTERFACE_H
#define UDPINTERFACE_H

#include <QUdpSocket>
#include <QHostAddress>

class UDPInterface : public QObject
{
    Q_OBJECT

public:
    UDPInterface();
    void setIP(QHostAddress ip);
    void setPort(quint16 port);
    void send(QByteArray packet, int packetSize);
    void start();
    void close();

private slots:
    void processPendingDatagrams();

signals:
    void new_packet_ready(QByteArray& i_packet);

private:

    QUdpSocket udpSocket4;
    QHostAddress groupAddress4;
    quint16 port;
};

#endif // UDPCOMMUNICATION_H
