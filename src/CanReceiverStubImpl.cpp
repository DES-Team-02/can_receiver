#include "CanReceiverStubImpl.hpp"

CanReceiverStubImpl::CanReceiverStubImpl() {}

CanReceiverStubImpl::~CanReceiverStubImpl() {}

void CanReceiverStubImpl::setSonarArrayStruct(uint32_t sensor0, uint32_t sensor1, uint32_t sensor2) {
    v0::commonapi::CanReceiver::SonarArrayStruct distances;
    distances.setSensorfrontleft(sensor0);
    distances.setSensorfrontmiddle(sensor1);
    distances.setSensorfrontright(sensor2);
    setDistancesAttribute(distances);
}
