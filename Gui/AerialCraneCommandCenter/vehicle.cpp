#include "vehicle.h"

Vehicle::Vehicle(const QString host_address, uint32_t port)
{
    mav_vehicle = new Connection(host_address, port);
    decode = new DecodeMavPackets(mav_vehicle);
    requestControlStateStream();
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
        uint16_t len = mavlink_msg_request_data_stream_pack(255, 0, &msg, 1, 0, streams[i], 1, 0);
        memcpy(&transmit_buffer[0], &msg, len);
        qint64 sent = mav_vehicle->transmit(&transmit_buffer[0], len);
        qDebug() << sent;
    }
}

Vehicle::~Vehicle()
{
    delete decode;
    delete mav_vehicle;
}
