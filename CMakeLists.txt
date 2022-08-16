cmake_minimum_required(VERSION 3.5)

project(usb-graph VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_BUILD_TYPE Debug)

add_executable(main main.cpp)

if(APPLE) # macOS
    FIND_PATH(
        LIBUSB_INCLUDE_DIR NAMES libusb.h
        HINTS /usr /usr/local /opt
        PATH_SUFFIXES libusb-1.0
    )
    set(LIBUSB_NAME libusb-1.0.dylib)
    find_library(
        LIBUSB_LIBRARY NAMES ${LIBUSB_NAME}
        HINTS /usr /usr/local /opt
    )

    if(NOT LIBUSB_NAME)
        message(FATAL_ERROR "No libusb library found on your system! Install libusb-1.0 from Homebrew or MacPorts")
    endif()
endif()

include_directories(${LIBUSB_INCLUDE_DIR})

target_link_libraries(main ${LIBUSB_LIBRARY})