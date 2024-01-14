cmake_minimum_required(VERSION 3.23)
project(TIP_services CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(database)
add_subdirectory(logger)
add_subdirectory(settings)