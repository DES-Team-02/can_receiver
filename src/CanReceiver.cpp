#include "CanReceiver.hpp"

CanReceiver::CanReceiver() : sensor0(0),sensor1(0),sensor2(0),running(false) {}

CanReceiver::~CanReceiver() {}

int CanReceiver::openPort(const char* iface) {
    struct ifreq ifr;           // Interface request structure for socket ioctls
    struct sockaddr_can addr;   // Address structure for the CAN socket

    // Open a CAN socket
    soc = socket(PF_CAN, SOCK_RAW, CAN_RAW);  
    // Check if socket is created successfully
    if (soc < 0) 
    {
	    std::cout << "Socket Creation Error!" << std::endl;
        return (-1);
    }
    // Set the family type for the address to CAN
    addr.can_family = AF_CAN;  
    // Copy the port name to the ifreq structure
    strcpy(ifr.ifr_name, CAN_INTERFACE);  
    // Get the interface index of the CAN device
    if (ioctl(soc, SIOCGIFINDEX, &ifr) < 0) 
    {
	    std::cout << "I/O Control Error." << std::endl;
        return (-1);
    }
    // Get the interface index from the ifreq structure
    addr.can_ifindex = ifr.ifr_ifindex;  
    // Set the socket to non-blocking mode
    fcntl(soc, F_SETFL, O_NONBLOCK);  
    // Bind the socket to the CAN interface
    if (bind(soc, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
	    std::cout << "Binding Error." << std::endl;
        return (-1);
    }
    return 0;
}

void CanReceiver::readData() {
    struct can_frame frame;     
    while(running) {
        // receive data
        ssize_t nbytes = recv(soc, &frame, sizeof(struct can_frame), MSG_WAITALL);
        // save timestamp if frame received
        if(nbytes == sizeof(struct can_frame)) {
            last_received_time = std::chrono::steady_clock::now();
        }
        switch(frame.can_id){
            case 0x200: 
            {
            // read raw data from frame & store
            std::lock_guard<std::mutex> lock(dataMutex);
            short received_sensor_0 = frame.data[0] << 8 | frame.data[1]; 
            short received_sensor_1 = frame.data[1] << 8 | frame.data[2]; 
            short received_sensor_2 = frame.data[3] << 8 | frame.data[4]; 

            sensor0 = received_sensor_0;
            sensor1 = received_sensor_1;
            sensor2 = received_sensor_2;
            }
        }
    }
}

void CanReceiver::processAndFilterData() {
    while(running) {        
        std::cout << "----------------------------------" << std::endl;
        std::cout << "Received Sensor0   : " << sensor0   << std::endl;
        std::cout << "Received Sensor1   : " << sensor1   << std::endl; 
        std::cout << "Received Sensor2   : " << sensor2   << std::endl;
        // send values to vSOME/IP
        dataRegister.sendDataToVSomeIP(static_cast<uint32_t>(filtered_rpm), static_cast<uint32_t>(filtered_speed));
    }
}

void CanReceiver::closePort() {
    close(soc);
}

int CanReceiver::run() {
    if (openPort(CAN_INTERFACE) < 0) {
        return -1;
    }

    running = true;
    last_received_time = std::chrono::steady_clock::now();

    std::thread readerThread(&CanReceiver::readData, this);
    std::thread processorThread(&CanReceiver::processAndFilterData, this);

    readerThread.join();
    processorThread.join();

    closePort();

    return 0;
}
