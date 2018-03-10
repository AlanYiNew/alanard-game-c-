cmake_minimum_required(VERSION 3.5)
project(Alanard)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

include_directories("include")
add_subdirectory(framework)
add_subdirectory(modules)

#set(SOURCE_FILES )
add_executable(gameServer main.cpp)
