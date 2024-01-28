#ifndef PDC_SENSORSTUBIMPL_HPP
#define PDC_SENSORSTUBIMPL_HPP

// Include necessary headers for CommonAPI
#include <CommonAPI/CommonAPI.hpp>
#include <v0/commonapi/PDCSensorStubDefault.hpp>

class PDCSensorStubImpl: public v0_1::commonapi::SpeedSensorStubDefault
{
public:
    PDCSensorStubImpl();
    virtual ~PDCSensorStubImpl();
};

#endif // PDC_SENSORSTUBIMPL_HPP
