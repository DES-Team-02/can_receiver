#include "ParkDistanceControlStubImpl.hpp"

ParkDistanceControlStubImpl::ParkDistanceControlStubImpl() {}

ParkDistanceControlStubImpl::~ParkDistanceControlStubImpl() {}

void ParkDistanceControlStubImpl::setSonarArrayStruct(uint32_t sensor0, uint32_t sensor1, uint32_t sensor2) {
    v0::commonapi::ParkDistanceControl::SonarArrayStruct distances;
    distances.setSensor0(sensor0);
    distances.setSensor1(sensor1);
    distances.setSensor2(sensor2);
    setBatteryAttribute(battery);
}
