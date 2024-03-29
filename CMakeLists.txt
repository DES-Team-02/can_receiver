### SETUP ###
cmake_minimum_required(VERSION 3.15)
project(Can_Receiver VERSION 0.1 LANGUAGES CXX)

### PACKAGES ###
find_package(CommonAPI REQUIRED)
find_package(CommonAPI-SomeIP REQUIRED)

### VARIABLES ###
## Application Information ##
set(APP_PACKAGE_NAME commonapi)
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
## Compiler Flags ##
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
## Install Directories ##
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for binaries")
set(INSTALL_INCLUDE_DIR include/CanReceiver CACHE PATH "Installation directory for header files")
set(DEF_INSTALL_CMAKE_DIR lib/cmake/CanReceiver-someip)
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")
foreach(p LIB INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(ABSOLUTE_${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()
## Executable Sources ##
set(Can_Receiver_SRCS
    ./src/main.cpp
    ./src/SpeedSensorStubImpl.cpp
    ./src/CanDataRegister.cpp
    ./src/MovingAverageFilter.cpp
    ./src/CanReceiver.cpp
)
## Library Sources ##
FILE(GLOB PRJ_SOMEIP_LIB_SRCS ./src-gen/someip/v${MAJOR_VERSION}/${APP_PACKAGE_NAME}/*.cpp)

### INCLUDE & LINK DIRECTORIES ###
include_directories(
	  ./include
    ./src-gen/core
    ./src-gen/someip
    ${COMMONAPI_INCLUDE_DIRS}
    ${COMMONAPI_SOMEIP_INCLUDE_DIRS}
)
link_directories(
    ${COMMONAPI_LIBDIR}
    ${COMMONAPI_SOMEIP_CMAKE_DIR}/build
)

### BUILD TARGETS ###
## Executable ## 
add_executable(CanReceiver 
    ${Can_Receiver_SRCS}
)
target_link_libraries(CanReceiver 
    CommonAPI
    CommonAPI-SomeIP 
    vsomeip3
  )

## Libaries ##
add_library(CanReceiver-someip
    SHARED ${PRJ_SOMEIP_LIB_SRCS}
)
target_link_libraries(CanReceiver-someip
    CommonAPI
    CommonAPI-SomeIP
)
## Properties ##
set_target_properties(CanReceiver-someip PROPERTIES 
    VERSION ${MAJOR_VERSION}.${MINOR_VERSION} 
    SOVERSION ${MAJOR_VERSION}.${MINOR_VERSION}
)
target_include_directories(CanReceiver-someip PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src-gen/core>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src-gen/someip>
    $<INSTALL_INTERFACE:${INSTALL_INCLUDE_DIR}>
)
set_target_properties (CanReceiver-someip PROPERTIES 
    INTERFACE_LINK_LIBRARY ""
)

### INSTALLATION ###
## Headers ##
file(GLOB_RECURSE HEADER_FILES "src-gen/core/v${MAJOR_VERSION}/${APP_PACKAGE_NAME}/*.hpp")
foreach(HEADER ${HEADER_FILES})
    get_filename_component(HEADER_ABS_PATH ${HEADER} ABSOLUTE)
    file(RELATIVE_PATH HEADER_REL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/src-gen/core ${HEADER_ABS_PATH})
    get_filename_component(HEADER_DIR ${HEADER_REL_PATH} DIRECTORY)
    install(FILES ${HEADER_ABS_PATH} DESTINATION ${INSTALL_INCLUDE_DIR}/${HEADER_DIR})
endforeach()
## Targets ##
install(TARGETS CanReceiver
        EXPORT CanReceiverTargets
        LIBRARY DESTINATION ${INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${INSTALL_BIN_DIR}
        ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
)
## Libraries ##
install(TARGETS CanReceiver-someip
        EXPORT CanReceiver-someipTargets
        LIBRARY DESTINATION ${INSTALL_LIB_DIR}
        RUNTIME DESTINATION ${INSTALL_BIN_DIR}
        ARCHIVE DESTINATION ${INSTALL_LIB_DIR}
        PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}"
)

### EXPORT ###
## Targets ##
# (Add all targets to the build-tree export set)
export(TARGETS CanReceiver-someip
  FILE "${PROJECT_BINARY_DIR}/CanReceiver-someipTargets.cmake"
)
#(Export the package for use from the build-tree(this registers the build-tree with a global CMake-registry)
export(PACKAGE CanReceiver-someip)
## Configuration files ##
#(Create the CanReceiver-someipConfig.cmake and CanReceiver-someipConfigVersion files ...)
file(RELATIVE_PATH REL_INCLUDE_DIR 
    "${ABSOLUTE_INSTALL_CMAKE_DIR}" "${ABSOLUTE_INSTALL_INCLUDE_DIR}"
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CanReceiver-someipConfig.cmake.in
  "${PROJECT_BINARY_DIR}/CanReceiver-someipConfig.cmake" @ONLY
)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CanReceiver-someipConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/CanReceiver-someipConfigVersion.cmake" @ONLY
)
install(FILES
  "${PROJECT_BINARY_DIR}/CanReceiver-someipConfig.cmake"
  "${PROJECT_BINARY_DIR}/CanReceiver-someipConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}"
)
install(EXPORT CanReceiver-someipTargets
  DESTINATION "${INSTALL_CMAKE_DIR}"
)
