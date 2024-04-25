#Minimum Vesrion
cmake_minimum_required(VERSION 3.10)
set(ENABLE_COVERAGE TRUE)
#Project Name
PROJECT(Circular_Buffer)
#Find Testing Packages
find_package(GTest REQUIRED)
#Define Include Directories
include_directories(${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/Include)
#Define Source Files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR} "Source/*.c" "Source/*.cpp")
#Adding Executable
add_executable(${PROJECT_NAME} ${SOURCES})
#Link With Testing Libs
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} GTest::GTest GTest::Main)
#Enable Discover Tests
gtest_discover_tests(${PROJECT_NAME})
#Add target to generate coverage reports
if(ENABLE_COVERAGE)
    #Edit Compiler Flag For Code Covearge
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 --coverage")
    #Create the directory for coverage reports
    file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Report)
    #Adding Rule For Generating Coverage Report
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Report/*
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/*.gcda
        COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --html --html-details -o ${CMAKE_BINARY_DIR}/Report/Coverage.html
        DEPENDS ${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating code coverage report"
    )
endif()