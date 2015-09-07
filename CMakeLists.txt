cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(mqtt CXX)
FILE(GLOB SRCFILES *.cpp)
add_executable(test_message ${SRCFILES})
set_property(TARGET test_message PROPERTY CXX_STANDARD 11)
set_property(TARGET test_message PROPERTY CXX_STANDARD_REQUIRED ON)

