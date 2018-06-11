#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_connect, SIGNAL(clicked()), this, SLOT(connect_drone()));
}

void MainWindow::connect_drone(){
    ardrone2 = new ArDrone2("192.168.1.1", 5556);
}

MainWindow::~MainWindow()
{
    delete ardrone2;
    delete ui;
}
