#Building Message
message(STATUS "================== Building My Applications ==================")
#Set Version
cmake_minimum_required(VERSION 3.0)
#Set Version
project(${Application_Name})
# Add the Wanted Application
add_subdirectory(${Application_Name})
message(STATUS "================ Application Build Finish ================")
