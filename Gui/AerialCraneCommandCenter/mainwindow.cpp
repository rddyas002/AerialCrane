#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mav_vehicles[0] = new Vehicle(MAVLINK_UDP_PORT1);
    mav_vehicles[1] = new Vehicle(MAVLINK_UDP_PORT2);
}



MainWindow::~MainWindow()
{
    delete ui;
}


