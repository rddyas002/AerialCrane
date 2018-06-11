#include "ardrone2.h"

ArDrone2::ArDrone2(const QString host_address, uint32_t port)
{
    timer.start();
    QHostAddress hostAddress = QHostAddress(host_address);
    udp_socket = new QUdpSocket(this);
    udp_socket->bind(hostAddress, port);

    seq = 1;

    connect(udp_socket, SIGNAL(readyRead()), this, SLOT(readData()));
    initialiseDrone();
}

void ArDrone2::readData(){
    while (udp_socket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udp_socket->receiveDatagram();
        qDebug() << datagram.data();
    }
}

void ArDrone2::initialiseDrone(void){
    QString data;

    data.asprintf("AT*CONFIG=%d\"general:navdata_demo\",\"TRUE\"\r", seq++);
    sendData(data.toUtf8());
    QThread::usleep(30000);

    data.asprintf("AT*CONFIG=%d,\"control:outdoor\",\"%s\"\rAT*CONFIG=%d,\"control:flight_without_shell\",\"%s\"\r", seq++, FLY_OUTDOOR, seq++, FLY_OUTDOOR);
    sendData(data.toUtf8());
    QThread::usleep(30000);

    data.asprintf("AT*CONFIG=%d,\"control:control_yaw\",\"%d\"\r", seq++, YAW_RATE);
    sendData(data.toUtf8());
    QThread::usleep(30000);

    data.asprintf("AT*CONFIG=%d,\"control:control_vz_max\",\"%d\"\r", seq++, THROTTLE_RATE);
    sendData(data.toUtf8());
    QThread::usleep(30000);

    data.asprintf("AT*CONFIG=%d,\"control:euler_angle_max\",\"0.%d\"\r", seq++, PITCH_ROLL_RATE);
    sendData(data.toUtf8());
    QThread::usleep(30000);

    data.asprintf("AT*CONFIG=%d,\"control:altitude_max\",\"%d\"\r", seq++, ALTITUDE_MAX);
    sendData(data.toUtf8());
    QThread::usleep(30000);

    data.asprintf("AT*LED=%d,2,1073741824,5\r", seq++);
    sendData(data.toUtf8());
    QThread::usleep(30000);
}

void ArDrone2::sendData(QByteArray ba){
    udp_socket->writeDatagram(ba);
}

void ArDrone2::land(void){
    QString data;
    data.asprintf("AT*PCMD=%d,0,0,0,0,0\rAT*REF=%d,%d\r", seq++, seq++, 290717696);
    udp_socket->writeDatagram(data.toUtf8());
}

void ArDrone2::resetWatchdog(void){
    seq = 1;
    QString data;
    data.asprintf("AT*COMWDG=%d\r", seq++);
    udp_socket->writeDatagram(data.toUtf8());
}

void ArDrone2::flatTrim(void){
    QString data;
    data.asprintf("AT*FTRIM=%d\rAT*LED=%d,2,1073741824,1\r", seq++, seq++);
    udp_socket->writeDatagram(data.toUtf8());
}

void ArDrone2::takeOff(float roll, float pitch, float heave_rate, float yaw_rate){
    QString data;
    data.asprintf("AT*REF=%d,290718208\rAT*PCMD=%d,0,%ld,%ld,%ld,%ld\r",
                  seq++, seq++, roll, pitch, heave_rate, yaw_rate);
    udp_socket->writeDatagram(data.toUtf8());
}

void ArDrone2::hoverControl(float roll, float pitch, float heave_rate, float yaw_rate){
    QString data;
    data.asprintf("AT*PCMD=%d,0,%ld,%ld,%ld,%ld\r",
                  seq++, roll, pitch, heave_rate, yaw_rate);
    udp_socket->writeDatagram(data.toUtf8());
}

void ArDrone2::flying(float roll, float pitch, float heave_rate, float yaw_rate){
    QString data;
    data.asprintf("AT*PCMD=%d,1,%ld,%ld,%ld,%ld\r",
                  seq++, roll, pitch, heave_rate, yaw_rate);
    udp_socket->writeDatagram(data.toUtf8());
}

ArDrone2::~ArDrone2() {
    land();
    QThread::sleep(1);
    delete udp_socket;
}
