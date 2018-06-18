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
    connect(ui->btn_takeoff,SIGNAL(clicked()), this, SLOT(takeoff1()));
    connect(ui->btn_arm,SIGNAL(clicked()), this, SLOT(setArm1()));
    connect(ui->btn_stream,SIGNAL(clicked()), this, SLOT(setStream1()));
    connect(ui->btn_land,SIGNAL(clicked()), this, SLOT(land1()));
}

void MainWindow::switchGuidedMode1(){
    vehicles[0]->setMode(COPTER_MODE_GUIDED);
}

void MainWindow::setArm1(void){
    vehicles[0]->mavCommandLong(MAV_CMD_COMPONENT_ARM_DISARM, 1, 0, 0, 0, 0, 0, 0);
}

void MainWindow::takeoff1(){
    float height = ui->txtHeight->toPlainText().toFloat();
    if (height > 100)
        height = 5;
    if (height < 0){
        qDebug("Height abnormal. Not taking off.");
        return;
    }
    vehicles[0]->mavTakeOff(height);
}

void MainWindow::land1(){
    vehicles[0]->setMode(COPTER_MODE_LAND);
}

void MainWindow::setStream1(){
    vehicles[0]->defaultDataStreamRate();
}

void MainWindow::connect_helicopter1(){
    vehicles[0] = new Vehicle(ui->txtIpH1->toPlainText(), ui->txtPortH1->toPlainText().toInt(), 0);
    ui->connectH1->setEnabled(false);
    ui->disconnectH1->setEnabled(true);
    connect(vehicles[0]->getDecoder(), SIGNAL(attitude_update_received(const mavlink_attitude_t *)), this, SLOT(update_attitude1(const mavlink_attitude_t *)));
    connect(vehicles[0]->getDecoder(), SIGNAL(gps_update_received(const mavlink_global_position_int_t *)), this, SLOT(update_gps1(const mavlink_global_position_int_t *)));
    connect(vehicles[0]->getDecoder(), SIGNAL(gps_raw_update_received(const mavlink_gps_raw_int_t *)), this, SLOT(update_gps_raw1(const mavlink_gps_raw_int_t *)));
    connect(vehicles[0]->getDecoder(), SIGNAL(heartbeat_update_received(const mavlink_heartbeat_t *)), this, SLOT(update_heartbeat1(const mavlink_heartbeat_t *)));
    connect(vehicles[0]->getDecoder(), SIGNAL(local_position_update_received(const mavlink_local_position_ned_t *)), this, SLOT(update_local_position1(const mavlink_local_position_ned_t *)));
}

void MainWindow::update_attitude1(const mavlink_attitude_t * mav_att){
    QString str;
    str.setNum(mav_att->roll*180/M_PI, 'g', 3);
    ui->rollLineEdit->setText(str);
    str.setNum(mav_att->pitch*180/M_PI, 'g', 3);
    ui->pitchLineEdit->setText(str);
    str.setNum(mav_att->yaw*180/M_PI, 'g', 3);
    ui->yawLineEdit->setText(str);
    str.setNum(mav_att->rollspeed*180/M_PI, 'g', 3);
    ui->rollRateLineEdit->setText(str);
    str.setNum(mav_att->pitchspeed*180/M_PI, 'g', 3);
    ui->pitchRateLineEdit->setText(str);
    str.setNum(mav_att->yawspeed*180/M_PI, 'g', 3);
    ui->yawRateLineEdit->setText(str);
}

void MainWindow::update_ahrs1(const mavlink_ahrs2_t * mav_ahrs2){
    QString str;
    str.setNum(mav_ahrs2->altitude, 'g', 3);
    ui->altitudeLineEdit->setText(str);
    str.setNum((double)mav_ahrs2->lat/1e7, 'g', 7);
    ui->latitudeLineEdit->setText(str);
    str.setNum((double)mav_ahrs2->lng/1e7, 'g', 7);
    ui->longitudeLineEdit->setText(str);
}

void MainWindow::update_gps1(const mavlink_global_position_int_t *mavlink_global_position_int){
    QString str;
    str.setNum((double)mavlink_global_position_int->alt/1000, 'g', 3);
    ui->altitudeLineEdit->setText(str);
    str.setNum((double)mavlink_global_position_int->lat/1e7, 'g', 7);
    ui->latitudeLineEdit->setText(str);
    str.setNum((double)mavlink_global_position_int->lon/1e7, 'g', 7);
    ui->longitudeLineEdit->setText(str);
    str.setNum((double)mavlink_global_position_int->relative_alt/1e3, 'g', 3);
    ui->rAltitudeLineEdit->setText(str);
    str.setNum((double)mavlink_global_position_int->hdg/100, 'g', 4);
    ui->headingLineEdit->setText(str);
    str.setNum((double)mavlink_global_position_int->vx/100, 'g', 2);
    ui->vxLineEdit->setText(str);
    str.setNum((double)mavlink_global_position_int->vy/100, 'g', 2);
    ui->vyLineEdit->setText(str);
    str.setNum((double)mavlink_global_position_int->vz/100, 'g', 2);
    ui->vzLineEdit->setText(str);
}

void MainWindow::update_gps_raw1(const mavlink_gps_raw_int_t *mavlink_gps_raw_int){
    QString str;
    str.setNum(mavlink_gps_raw_int->fix_type);
    ui->fixedLineEdit->setText(str);
    str.setNum(mavlink_gps_raw_int->eph);
    ui->hDOPLineEdit->setText(str);
    str.setNum(mavlink_gps_raw_int->satellites_visible);
    ui->satellitesLineEdit->setText(str);
}

void MainWindow::update_heartbeat1(const mavlink_heartbeat_t *mavlink_heartbeat){
    static bool toggle = true;
    toggle = !toggle;
    if (toggle){
        ui->lblHeartbeat->setStyleSheet("QLabel { background-color : red;}");
    }
    else{
        ui->lblHeartbeat->setStyleSheet("QLabel { background-color : white;}");
    }
}

void MainWindow::update_local_position1(const mavlink_local_position_ned_t *mavlink_local_position_ned){
    QString str;
    str.setNum((double)mavlink_local_position_ned->x, 'g', 3);
    ui->xLineEdit->setText(str);
    str.setNum((double)mavlink_local_position_ned->y, 'g', 3);
    ui->yLineEdit->setText(str);
    str.setNum((double)mavlink_local_position_ned->z, 'g', 3);
    ui->zLineEdit->setText(str);
    str.setNum((double)mavlink_local_position_ned->vx, 'g', 3);
    ui->vxLineEdit_2->setText(str);
    str.setNum((double)mavlink_local_position_ned->vy, 'g', 3);
    ui->vyLineEdit_2->setText(str);
    str.setNum((double)mavlink_local_position_ned->vz, 'g', 3);
    ui->vzLineEdit_2->setText(str);
}

void MainWindow::connect_helicopter2(){
    vehicles[1] = new Vehicle(ui->txtIpH2->toPlainText(), ui->txtPortH2->toPlainText().toInt(),1);
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


