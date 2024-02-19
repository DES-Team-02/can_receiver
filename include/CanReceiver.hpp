#ifndef CAN_RECEIVER_HPP
#define CAN_RECEIVER_HPP

#include "CanDataRegister.hpp"

#include <fcntl.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <cmath>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>

class CanReceiver {
public:
    CanReceiver();
    ~CanReceiver();
    int run();

private:
    CanDataRegister dataRegister;

    const char* CAN_INTERFACE = "can1";
    
    int soc;
    std::mutex dataMutex;

    short sensor0;
    short sensor1; 
    short sensor2; 

    std::atomic<bool> running;
    std::chrono::steady_clock::time_point last_received_time;

    int openPort(const char* iface);
    void readData();
    void processAndFilterData();
    void closePort();
};

#endif  //  CAN_RECEIVER_HPP
