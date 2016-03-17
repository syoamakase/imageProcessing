# Copyright: (C) 2010 RobotCub Consortium
# Author: Paul Fitzpatrick
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
# YARP needs CMake 2.8.9 or greater
cmake_minimum_required(VERSION 2.8.9)
# find YARP
find_package(YARP REQUIRED)
# add YARP include directories
include_directories(${YARP_INCLUDE_DIRS})
# set up our program
add_executable(findLocationTCP findLocationTCP.cpp)
# link with YARP libraries
add_definitions(-std=c++11)
target_link_libraries(findLocationTCP ${YARP_LIBRARIES})
target_link_libraries(findLocationTCP boost_system)
target_link_libraries(findLocationTCP boost_thread)
target_link_libraries(findLocationTCP pthread)
