cmake_minimum_required(VERSION 3.20)
project(paraflop VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(monads_demo ${CMAKE_SOURCE_DIR}/src/monads_demo.cpp)
target_include_directories(monads_demo PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(monads_demo PUBLIC -Wall -Wextra -pedantic -Ofast)
