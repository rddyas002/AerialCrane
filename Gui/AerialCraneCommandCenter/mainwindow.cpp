#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpSocket[0] = new QUdpSocket(this);
    udpSocket[1] = new QUdpSocket(this);
    udpSocket[0]->bind(QHostAddress::LocalHost, MAVLINK_UDP_PORT1);
    udpSocket[1]->bind(QHostAddress::LocalHost, MAVLINK_UDP_PORT2);

    connect(udpSocket[0], SIGNAL(readyRead()), this, SLOT(readPendingDatagramsSocket1()));
    connect(udpSocket[1], SIGNAL(readyRead()), this, SLOT(readPendingDatagramsSocket2()));
}

void MainWindow::readPendingDatagramsSocket1()
{
    while (udpSocket[0]->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket[0]->receiveDatagram();
        for (int i = 0; i < datagram.data().length(); i++){
            if (mavlink_parse_char(MAVLINK_COMM_0, datagram.data()[i], &msg[0], &status[0])){
                printf("[1] Received message with ID %d, sequence: %d from component %d of system %d\n", msg[0].msgid, msg[0].seq, msg[0].compid, msg[0].sysid);
/*
                if (msg[0].msgid == MAVLINK_MSG_ID_HEARTBEAT){
                    mavlink_heartbeat_t mavlink_heartbeat;
                    mavlink_msg_heartbeat_decode(&msg[0], &mavlink_heartbeat);
                    printf("Received Heartbeat from ID: %u TYPE: %u AUTOPILOT: %u.\r\n",
                           msg[0].sysid,
                           mavlink_heartbeat.type,
                           mavlink_heartbeat.autopilot);

                }
  */
          }
        }
    }
}

void MainWindow::readPendingDatagramsSocket2()
{
    while (udpSocket[1]->hasPendingDatagrams()) {
        QNetworkDatagram datagram = udpSocket[1]->receiveDatagram();
        for (int i = 0; i < datagram.data().length(); i++){
            if (mavlink_parse_char(MAVLINK_COMM_1, datagram.data()[i], &msg[1], &status[1])){
                printf("[2] Received message with ID %d, sequence: %d from component %d of system %d\n", msg[1].msgid, msg[1].seq, msg[1].compid, msg[1].sysid);
/*
                if (msg[1].msgid == MAVLINK_MSG_ID_HEARTBEAT){
                    mavlink_heartbeat_t mavlink_heartbeat;
                    mavlink_msg_heartbeat_decode(&msg[1], &mavlink_heartbeat);
                    printf("Received Heartbeat from ID: %u TYPE: %u AUTOPILOT: %u.\r\n",
                           msg[1].sysid,
                           mavlink_heartbeat.type,
                           mavlink_heartbeat.autopilot);

                }
                */
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    udpSocket[0]->close();
    udpSocket[1]->close();
}


