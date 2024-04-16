#Building Message
message(STATUS "================== Building Application ==================")
#Set Version
cmake_minimum_required(VERSION 3.22)
#Set Project Name   
project(Test_CPP VERSION 22.22)
#Set CPP Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
#Locate Source Files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR} "Source/*.c" "Source/*.cpp")
#Building Message
message(STATUS "Files To Be Compiled : ${SOURCES}")
#Edit In Default Location of .cmake files
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Libraries/CMake")
#Add Executable
add_executable(${PROJECT_NAME} ${SOURCES})
# Specify include directories
include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Include/ ${LIBRARY_INCLUDES})
#Building Message
message(STATUS "================ Application Build Finish ================")

