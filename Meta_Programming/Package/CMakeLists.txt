# Building Message
message(STATUS "================== Building Library ==================")
# Select Minimum Version
cmake_minimum_required(VERSION 3.12)
# Set Library Version
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
# Specify Project Name
project(Mathlib VERSION 1.0)
# Set Library Name
set(Package_Name MyPackage)
# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Add library source files
file(GLOB_RECURSE SOURCES "Source/*.c" "Source/*.cpp")
# Building Message
message(STATUS "Files To Be Compiled : ${SOURCES}")
# Create a library
add_library(${PROJECT_NAME} SHARED ${SOURCES})
# Install Library CMake File
install(TARGETS ${PROJECT_NAME} EXPORT ${Package_Name} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# Edit Default Find<name>cmake Location
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
# Set Version Property
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
# Install CMake File
install(EXPORT ${Package_Name} FILE "Find${Package_Name}.cmake" DESTINATION ${CMAKE_MODULE_PATH})
# Specify include directories for the library
include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
#target_include_directories(${PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> $<INSTALL_INTERFACE:include>)
# Building Message
message(STATUS "================ Library Build Finish ================")
