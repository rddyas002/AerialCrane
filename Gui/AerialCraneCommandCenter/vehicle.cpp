#include "vehicle.h"

Vehicle::Vehicle(const QString host_address, uint32_t port)
{
    mav_vehicle = new Connection(host_address, port);
    decode = new DecodeMavPackets(mav_vehicle);
}

Vehicle::~Vehicle()
{
    delete decode;
    delete mav_vehicle;
}
