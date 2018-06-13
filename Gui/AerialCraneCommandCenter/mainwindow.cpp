#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QScrollBar>

#define MAVLINK_UDP_IP      "10.24.5.30"
#define MAVLINK_UDP_LOCAL   "127.0.0.1"
#define MAVLINK_UDP_IP2      "192.168.4.2"
#define MAVLINK_UDP_PORT1    14550
#define MAVLINK_UDP_PORT2    14560

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->connectH1,SIGNAL(clicked()), this, SLOT(connect_helicopter1()));
    connect(ui->connectH2,SIGNAL(clicked()), this, SLOT(connect_helicopter2()));
    connect(ui->disconnectH1,SIGNAL(clicked()), this, SLOT(disconnect_helicopter1()));
    connect(ui->disconnectH2,SIGNAL(clicked()), this, SLOT(disconnect_helicopter2()));
    ui->disconnectH1->setEnabled(false);

    connect(ui->btn_guided,SIGNAL(clicked()), this, SLOT(switchGuidedMode1()));
}

void MainWindow::switchGuidedMode1(){
    vehicles[0]->mavTakeOff();
}

void MainWindow::connect_helicopter1(){
    vehicles[0] = new Vehicle(ui->txtIpH1->toPlainText(), ui->txtPortH1->toPlainText().toInt());
    ui->connectH1->setEnabled(false);
    ui->disconnectH1->setEnabled(true);
}

void MainWindow::connect_helicopter2(){
    vehicles[1] = new Vehicle(ui->txtIpH2->toPlainText(), ui->txtPortH2->toPlainText().toInt());
}

void MainWindow::disconnect_helicopter1(){
    if (vehicles[0] != NULL){
        delete vehicles[0];
        ui->connectH1->setEnabled(true);
        ui->disconnectH1->setEnabled(false);
    }

}

void MainWindow::disconnect_helicopter2(){
    if (vehicles[1] != NULL)
        delete vehicles[1];
}

MainWindow::~MainWindow()
{
    delete ui;
}


