#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::LocalHost, MAVLINK_UDP_PORT);

    connect(udpSocket, SIGNAL(readyRead()),
                this, SLOT(readPendingDatagrams()));
/*
    serialPort = new QSerialPort(this);
    serialPort->setPortName("/dev/ttyACM0");
    serialPort->setBaudRate(QSerialPort::Baud57600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    serialPort->open(QIODevice::ReadWrite);

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(serialReceived()));
    */
}

void MainWindow::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket->receiveDatagram();
        processDataReceived(datagram.data());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    udpSocket->close();
    //serialPort->close();
}

void MainWindow::processDataReceived(QByteArray ba){
    for (int i = 0; i < ba.length(); i++){
        if (mavlink_parse_char(MAVLINK_COMM_0, ba.data()[i], &msg, &status)){
            //printf("Received message with ID %d, sequence: %d from component %d of system %d\n", msg.msgid, msg.seq, msg.compid, msg.sysid);

            if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT){
                mavlink_heartbeat_t mavlink_heartbeat;
                mavlink_msg_heartbeat_decode(&msg, &mavlink_heartbeat);
                printf("Received Heartbeat from ID: %u TYPE: %u AUTOPILOT: %u.\r\n",
                       msg.sysid,
                       mavlink_heartbeat.type,
                       mavlink_heartbeat.autopilot);

            }
        }
    }
}

void MainWindow::serialReceived()
{
    int i;
    char data[MAVLINK_MAX_PACKET_LEN];

    uint8_t len = serialPort->read(&data[0], MAVLINK_MAX_PACKET_LEN);
    for (i = 0; i < len; i++){
        if (mavlink_parse_char(MAVLINK_COMM_0, data[i], &msg, &status)){
            printf("Received message with ID %d, sequence: %d from component %d of system %d", msg.msgid, msg.seq, msg.compid, msg.sysid);

            if (msg.msgid == MAVLINK_MSG_ID_HEARTBEAT){
                mavlink_heartbeat_t mavlink_heartbeat;
                mavlink_msg_heartbeat_decode(&msg, &mavlink_heartbeat);
                printf("Received Heartbeat from ID %d.\n", msg.sysid);

            }
        }
    }
    qDebug() << len;
}
