#include "vehicle.h"

Vehicle::Vehicle(const QString host_address, uint32_t port)
{
    mav_vehicle = new Connection(host_address, port);
    decode = new DecodeMavPackets(mav_vehicle);
    requestControlStateStream();
}

void Vehicle::requestControlStateStream(void){
    mavlink_message_t msg;
    uint16_t len = mavlink_msg_request_data_stream_pack(255, 0, &msg, 1, 1, MAV_DATA_STREAM_EXTENDED_STATUS, 5, 1);
    char * data = (char *)malloc(len + 1);
    *data = 0xFE;
    memcpy(data + 1, &msg, len);
    qint64 sent = mav_vehicle->transmit(data, len + 1);
    qDebug() << sent;
    delete data;
}

Vehicle::~Vehicle()
{
    delete decode;
    delete mav_vehicle;
}
