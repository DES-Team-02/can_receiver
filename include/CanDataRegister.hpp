#ifndef CAN_DATA_REGISTER_HPP
#define CAN_DATA_REGISTER_HPP

#include <iostream>
#include <CommonAPI/CommonAPI.hpp>
#include "CanReceiverStubImpl.hpp" 

using namespace v0_1::commonapi;

class CanDataRegister {
public:
    CanDataRegister();
    virtual ~CanDataRegister();
    void setServiceAttributes(uint32_t rpm, uint32_t speed, uint32_t sensor0, uint32_t sensor1, uint32_t sensor2); 
private:
    std::shared_ptr<CommonAPI::Runtime> runtime;
    std::shared_ptr<CanReceiverImpl> CanReceiverService;
    void CanReceiverInit();
};

#endif //CAN_DATA_REGISTER_HPP
