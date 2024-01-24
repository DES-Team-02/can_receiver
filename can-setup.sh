#!/bin/bash

# Set CAN interface 
sudo ip link set can1 up type can bitrate 500000

# Set txqueuelen 
sudo ifconfig can1 txqueuelen 65536
