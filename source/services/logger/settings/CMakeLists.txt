cmake_minimum_required(VERSION 3.23)
project(TIP_settings CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} settings.cpp)