#include <QtWidgets>

#include "udpinterface.h"


UDPInterface::UDPInterface()
{}

void UDPInterface::setIP(QHostAddress ip)
{
    groupAddress4 = ip;
}


void UDPInterface::setPort(quint16 port)
{

    this->port = port;
}

void UDPInterface::send(QByteArray packet, int packetSize)
{
    udpSocket4.writeDatagram(packet,
                             packetSize,
                             groupAddress4,
                             port);
}

void UDPInterface::start()
{
    udpSocket4.bind(QHostAddress::AnyIPv4, port, QUdpSocket::ShareAddress | QUdpSocket::ShareAddress );
    udpSocket4.joinMulticastGroup(groupAddress4);
    connect(&udpSocket4, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

void UDPInterface::processPendingDatagrams()
{
    QByteArray data;

    // using QUdpSocket::readDatagram (API since Qt 4)
    while (udpSocket4.hasPendingDatagrams()) {
        data.resize(int(udpSocket4.pendingDatagramSize()));
        udpSocket4.readDatagram(data.data(), data.size());

        emit new_packet_ready(data);

        qDebug() << "packet size: " << data.size() << " | " << data.data();
    }
}

void UDPInterface::close()
{
    udpSocket4.leaveMulticastGroup(groupAddress4);
    udpSocket4.close();
    groupAddress4.clear();
}

