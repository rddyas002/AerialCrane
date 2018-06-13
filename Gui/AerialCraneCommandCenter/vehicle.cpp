#include "vehicle.h"

Vehicle::Vehicle(const QString host_address, uint32_t port)
{
    this_sysid = 255;
    this_compid = 0;
    target_sysid = 1;
    target_compid = 1;

    mav_vehicle = new Connection(port);
    decode = new DecodeMavPackets(mav_vehicle);
    //requestControlStateStream();
    timer_1second = new QTimer(this);
    connect(timer_1second, SIGNAL(timeout()), this, SLOT(oneSecondTimer()));
    timer_1second->start(1000);
}

void Vehicle::oneSecondTimer(void){
   //mavSendHeartbeat();
}

void Vehicle::mavSendHeartbeat(void){
    mavlink_message_t msg;

    uint16_t len = mavlink_msg_heartbeat_pack(this_sysid, this_compid, &msg, MAV_TYPE_GCS, MAV_AUTOPILOT_INVALID, MAV_MODE_MANUAL_ARMED, 0, MAV_STATE_STANDBY);
    qint64 sent = mav_vehicle->transmit((const char *)&msg, len);
}

void Vehicle::mavTakeOff(void){
    mavlink_message_t msg;
    uint16_t len = mavlink_msg_command_long_pack(this_sysid, this_compid, &msg, target_sysid, target_compid, MAV_CMD_NAV_TAKEOFF, 0, 0, 0, 0, 0, 0, 0, 20);
    qint64 sent = mav_vehicle->transmit((const char *)&msg, len);
}

void Vehicle::requestControlStateStream(void){
    mavlink_message_t msg;
    uint8_t streams[10] = {MAV_DATA_STREAM_ALL,
        MAV_DATA_STREAM_RAW_SENSORS,
        MAV_DATA_STREAM_EXTENDED_STATUS,
        MAV_DATA_STREAM_RC_CHANNELS,
        MAV_DATA_STREAM_RAW_CONTROLLER,
        MAV_DATA_STREAM_POSITION,
        MAV_DATA_STREAM_EXTRA1,
        MAV_DATA_STREAM_EXTRA2,
        MAV_DATA_STREAM_EXTRA3,
        MAV_DATA_STREAM_ENUM_END};
    for (int i = 0; i < 10; i++){
        uint16_t len = mavlink_msg_request_data_stream_pack(this_sysid, this_compid, &msg, target_sysid, target_compid, streams[i], 1, 0);
        memcpy(&transmit_buffer[0], &msg, len);
        qint64 sent = mav_vehicle->transmit(&transmit_buffer[0], len);
        qDebug() << sent;
    }
}

void Vehicle::setMode(uint32_t mode){
    mavlink_message_t msg;
    uint16_t len = mavlink_msg_set_mode_pack(this_sysid, this_compid, &msg, target_sysid, 1, mode);
    qint64 sent = mav_vehicle->transmit((const char *)&msg, len);
    qDebug() << sent;

}

Vehicle::~Vehicle()
{
    delete decode;
    delete mav_vehicle;
}
