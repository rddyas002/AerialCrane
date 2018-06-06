#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mav_vehicles[0] = new Connection(MAVLINK_UDP_IP2, MAVLINK_UDP_PORT1);
    decode[0] = new DecodeMavPackets(mav_vehicles[0]);
}



MainWindow::~MainWindow()
{
    delete ui;
    //delete mav_vehicles[0];
}


