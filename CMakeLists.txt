#Building Message
message(STATUS "================== Building Application ==================")
#Set Version
cmake_minimum_required(VERSION 3.0)
#Set Project Name   
project(Test_CPP VERSION 22.22)
#Locate Source Files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR} "Source/*.c" "Source/*.cpp")
#Building Message
message(STATUS "Files To Be Compiled : ${SOURCES}")
# Specify include directories
include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Include/)
#Add Executable
add_executable(${PROJECT_NAME} ${SOURCES})
# Set install directory to binary directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
# Install executable to binary directory
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#Building Message
message(STATUS "================ Application Build Finish ================")

