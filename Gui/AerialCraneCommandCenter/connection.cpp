#include "connection.h"

Connection::Connection(const QString host_address, uint32_t port)
{
    timer.start();
    QHostAddress hostAddress = QHostAddress(host_address);
    udp_socket = new QUdpSocket(this);
    udp_socket->bind(hostAddress, port);
    //QAbstractSocket::connectToHost(ip_address, port);
    connect(udp_socket, SIGNAL(readyRead()), this, SLOT(readData()));
}


void Connection::readData()
{
    while (udp_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp_socket->receiveDatagram();
        for (int i = 0; i < datagram.data().length(); i++){
            if (mavlink_parse_char(MAVLINK_COMM_0, datagram.data()[i], &msg, &status)){
                emit Connection::MavLinkPacketReceived(&msg, timer.elapsed());
          }
        }
    }
}

Connection::~Connection()
{
    delete udp_socket;
}
