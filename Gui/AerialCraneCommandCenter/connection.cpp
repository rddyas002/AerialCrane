#include "connection.h"
#include <QAbstractSocket>
#include <QNetworkProxy>

Connection::Connection(uint32_t port, uint8_t channel){
    first_connect = false;
    mav_channel = channel;
    timer.start();
    udp_port = port;
    hostAddress = QHostAddress::AnyIPv4;
    udp_socket = new QUdpSocket(this);
    udp_socket->setProxy(QNetworkProxy::NoProxy);
    if(udp_socket->bind(hostAddress, udp_port))
        qDebug() << "UDP port " << udp_port << " opened";
    else
        qDebug() << "Failed to bind";

    udp_socket->setSocketOption(QAbstractSocket::SendBufferSizeSocketOption,    256 * 1024);
    udp_socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 512 * 1024);

    connect(udp_socket, SIGNAL(readyRead()), this, SLOT(readData()));
}

qint64 Connection::transmit(const char *data, qint64 size){
    if (first_connect){
        qint64 len = udp_socket->writeDatagram(data, size, senderAddress, senderPort);
        return len;
    }
}

void Connection::readData()
{
    while (udp_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp_socket->receiveDatagram();
        if (!first_connect){
            senderAddress = datagram.senderAddress();
            senderPort = datagram.senderPort();
            qDebug() << "Received packet from " << senderAddress << ". Sender port: " << senderPort;
            first_connect = true;
        }
        for (int i = 0; i < datagram.data().length(); i++){
            if (mavlink_parse_char(mav_channel, datagram.data()[i], &msg, &status)){
                emit Connection::MavLinkPacketReceived(&msg, timer.elapsed());
          }
        }
    }
}

Connection::~Connection()
{
    qDebug() << "UDP port " << udp_port << " closed";
    delete udp_socket;
}
