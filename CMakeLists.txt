cmake_minimum_required(VERSION 3.23)
project(TIP CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOUIC_SEARCH_PATHS source/ui/)

set(CMAKE_PREFIX_PATH E:/Development/CPP/Libraries) # path/to/Qt5

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../build) # path/to/build_directory

add_subdirectory(source)