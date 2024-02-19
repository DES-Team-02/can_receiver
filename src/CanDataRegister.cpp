#include "CanDataRegister.hpp"
#include <iostream>
#include <thread>
using namespace v0_1::commonapi;

/*Constructor.*/
CanDataRegister::CanDataRegister() {
    // Get the commonAPI runtime instance & create the vSOME/IP service
    runtime = CommonAPI::Runtime::get();
    ParkDistanceControlService = std::make_shared<ParkDistanceControlStubImpl>();
    // Register the SOME/IP service
    SpeedSensor_Init();
}

/*Destructor*/
CanDataRegister::~CanDataRegister() {}

/* Registers the vSOME/IP service*/
void CanDataRegister::ParkDistanceControlInit(){
    while(!runtime->registerService("local", "commonapi.ParkDistanceControl", ParkDistanceService, "ParkDistanceControlService")){
        std::cout << "Register ParkDistance Service failed, trying again in 100 milliseconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "Successfully Registered ParkDistance Service!" << std::endl;
}

/* sets the attributes of vSOME/IP service*/
void CanDataRegister::setServiceAttributes(uint32_t sensor0, uint32_t sensor1, uint32_t sensor2) {
    // set via StubImpl
    ParkDistanceControlService->setSonarArrayStruct();
}